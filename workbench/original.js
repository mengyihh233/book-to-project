/* 原书阅读器：页图为主，原文为可选层；旁侧只链接既有任务，不新建任务也不写进度。 */
(() => {
  const $ = (id) => document.getElementById(id);
  const TOTAL = 659;
  const DEFAULT_PAGE = 206;
  const state = { page: DEFAULT_PAGE, mode: 'image', fit: true, zoom: 100, manifest: null, textRequest: 0 };

  const esc = (value) => String(value ?? '');
  const pageLabel = (page) => 'PDF 第 ' + page + ' 页';

  function toast(message) {
    const box = $('or-status');
    box.textContent = message;
    box.classList.add('show');
    clearTimeout(toast.timer);
    toast.timer = setTimeout(() => box.classList.remove('show'), 2200);
  }

  function clampPage(value) {
    const number = Number.parseInt(value, 10);
    if (!Number.isFinite(number)) return state.page;
    return Math.min(TOTAL, Math.max(1, number));
  }

  function docLink(path) {
    return '/workbench/help.html?doc=' + encodeURIComponent(path);
  }

  function entryFor(page) {
    const pages = state.manifest?.pages || [];
    return pages.find((item) => item.pdf_page === page) || null;
  }

  function rangeText() {
    const ranges = state.manifest?.ranges
      || (state.manifest?.verified_range?.length ? [state.manifest.verified_range] : []);
    if (!ranges.length) return '暂无';
    return ranges.map((r) => (r[0] === r[1] ? 'PDF ' + r[0] : 'PDF ' + r[0] + '—' + r[1])).join('、');
  }

  function scaleFor() {
    const dpr = window.devicePixelRatio || 1;
    const base = dpr >= 2 ? 2.6 : 2.2;
    const zoomed = !state.fit && state.zoom > 140;
    return Math.min(4, Math.max(1, zoomed ? base + 1.2 : base));
  }

  function renderImage(force) {
    const image = $('or-img');
    const url = '/api/original/page/' + state.page + '.png?scale=' + scaleFor().toFixed(2);
    if (force || image.dataset.url !== url) {
      image.dataset.url = url;
      image.src = url;
    }
    image.classList.toggle('zoomed', !state.fit);
    image.style.width = state.fit ? '100%' : state.zoom + '%';
    image.alt = pageLabel(state.page) + ' 的原页影像';
    const entry = entryFor(state.page);
    $('or-cap').textContent = entry
      ? pageLabel(state.page) + (entry.printed_page != null ? '（印刷页 ' + entry.printed_page + '）' : '') + '· 原页影像，未做任何文字替换'
      : pageLabel(state.page) + ' · 原页影像（本页尚未识别校对）';
  }

  function badges(entry) {
    const box = $('or-badges');
    box.replaceChildren();
    const add = (text, kind) => {
      const span = document.createElement('span');
      span.className = 'or-badge' + (kind ? ' ' + kind : '');
      span.textContent = text;
      box.append(span);
    };
    add('原页影像', 'plain');
    if (!entry) {
      add('未发布原文');
      add('不提供转写', 'warn');
      return;
    }
    if (entry.status === 'reviewed') add('已校对原文', 'ok');
    else if (entry.status === 'needs_review') add('OCR 待校对', 'warn');
    else add('仅原页影像', 'warn');
    if (entry.open_questions > 0) add('待核对 ' + entry.open_questions + ' 处', 'warn');
  }

  function renderPanel() {
    const entry = entryFor(state.page);
    $('or-panel-title').textContent = pageLabel(state.page) + (entry?.printed_page != null ? ' · 印刷页 ' + entry.printed_page : '');
    badges(entry);

    const info = $('or-pageinfo');
    info.replaceChildren();
    const line = (text) => {
      const div = document.createElement('div');
      div.textContent = text;
      info.append(div);
    };
    if (entry) {
      line('小节：' + entry.sections.join('、'));
      line('识别状态：' + (entry.status === 'reviewed' ? '已逐页校对（可切换“已校对原文”）' : '待校对'));
    } else {
      line('本页只剩原页影像：尚未纳入识别批次，因此不显示任何转写文本。');
      line('已校对范围：' + rangeText() + '。');
    }

    const sections = $('or-sections');
    sections.replaceChildren();
    let lastChapter = null;
    let activeButton = null;
    for (const item of state.manifest?.sections || []) {
      const chapter = String(item.id).split('.')[0];
      if (chapter !== String(entry?.chapter ?? '')) continue;
      if (chapter !== lastChapter) {
        const label = document.createElement('div');
        label.className = 'or-chap';
        label.textContent = '第 ' + chapter + ' 章';
        sections.append(label);
        lastChapter = chapter;
      }
      const button = document.createElement('button');
      button.type = 'button';
      button.textContent = item.title;
      const own = (entry?.sections || []).includes(item.id);
      button.classList.toggle('active', own);
      if (own) activeButton = button;
      button.onclick = () => {
        const target = (state.manifest?.pages || []).find((p) => p.sections.includes(item.id));
        if (target) go(target.pdf_page);
      };
      sections.append(button);
    }
    if (activeButton) {
      const boxRect = sections.getBoundingClientRect();
      const btnRect = activeButton.getBoundingClientRect();
      const offset = btnRect.top - boxRect.top + sections.scrollTop - sections.clientHeight / 2 + btnRect.height / 2;
      sections.scrollTop = Math.max(0, offset);
    }
    if (!sections.children.length) {
      const p = document.createElement('div');
      p.className = 'or-notes';
      p.textContent = '本批目录尚未发布。';
      sections.append(p);
    }

    const links = $('or-links');
    links.replaceChildren();
    const link = (href, title, note, external) => {
      const a = document.createElement('a');
      a.href = href;
      if (external) {
        a.target = '_blank';
        a.rel = 'noopener noreferrer';
      }
      const strong = document.createElement('strong');
      strong.textContent = title;
      const span = document.createElement('span');
      span.textContent = note;
      a.append(strong, span);
      links.append(a);
      return a;
    };
    const detailsBlock = (title, build) => {
      const details = document.createElement('details');
      const summary = document.createElement('summary');
      summary.textContent = title;
      const holder = document.createElement('div');
      holder.className = 'or-links';
      holder.style.marginTop = '8px';
      details.append(summary, holder);
      links.append(details);
      build((href, text, note) => {
        const a = document.createElement('a');
        a.href = href;
        a.target = '_blank';
        a.rel = 'noopener noreferrer';
        const strong = document.createElement('strong');
        strong.textContent = text;
        const span = document.createElement('span');
        span.textContent = note || '';
        a.append(strong, span);
        holder.append(a);
      });
    };

    const chapter = state.manifest?.chapter_links?.[String(entry?.chapter ?? '')] || null;
    const main = chapter?.main || null;
    if (entry?.chapter) link('/workbench/chapter.html?chapter=' + entry.chapter + '#page=' + state.page,
      '按章连续阅读', '在同一篇正文中阅读本章，附小节目录与练习入口');
    if (main) {
      link(main.deep_link || '/#task=' + encodeURIComponent(main.id), '打开本题：' + main.title,
        main.id + ' · 题目与自己的作答入口', true);
      if (main.work) link('/' + main.work, '查看本章作答（只读）', main.work, true);
      if (main.commentary) link(docLink(main.commentary), '本章中文阅读注释', '自编概括，不是原书原文');
    }
    if (main?.answer) detailsBlock('参考解析（先自己写，再展开）', (add) => add(docLink(main.answer), '本章参考解析', main.answer));
    for (const project of chapter?.projects || []) {
      link(docLink(project.readme), project.title, project.relation);
    }
    if (chapter?.review_page) {
      link('/books/cpp-roberts.pdf#page=' + chapter.review_page, '本章复习（PDF ' + chapter.review_page + '）', '原 PDF 页码跳转', true);
    }
    if (chapter?.exercise_page) {
      link('/books/cpp-roberts.pdf#page=' + chapter.exercise_page, '本章相关练习（PDF ' + chapter.exercise_page + '）',
        '原书习题页；只标「本章相关练习」，不声称逐段精确对应', true);
    }
    if ((chapter?.exercises || []).length) {
      detailsBlock('本章原书题（' + chapter.exercises.length + ' 道）', (add) => {
        for (const exercise of chapter.exercises) {
          add('/#task=' + encodeURIComponent(exercise.id), exercise.id + ' · ' + exercise.title,
            'PDF ' + exercise.pdf_page + ' · 打开题目与自己的作答入口');
        }
      });
    }
    if (!chapter) {
      const note = document.createElement('div');
      note.className = 'or-notes';
      note.textContent = '本章尚未登记练习任务。';
      links.append(note);
    }

    const figures = $('or-figures');
    figures.replaceChildren();
    const published = (state.manifest?.pages || []).find((p) => p.pdf_page === state.page);
    const names = (state.manifest?.figures?.[String(state.page)]) || [];
    if (!names.length && published?.figure_count) {
      const note = document.createElement('div');
      note.className = 'or-notes';
      note.textContent = '本页图示见“已校对原文”层。';
      figures.append(note);
    }
    for (const name of names) {
      const a = document.createElement('a');
      a.href = '/api/original/figure/' + encodeURIComponent(name);
      a.target = '_blank';
      a.rel = 'noopener noreferrer';
      const img = document.createElement('img');
      img.src = a.href;
      img.alt = '第 ' + state.page + ' 页图示';
      img.loading = 'lazy';
      a.append(img);
      figures.append(a);
    }

    const uncertain = $('or-uncertain');
    uncertain.replaceChildren();
    const items = state.manifest?.uncertain?.[String(state.page)] || [];
    if (!items.length) {
      const div = document.createElement('div');
      div.textContent = entry ? '本页没有未解决的待核对项。' : '本页未识别，无待核对记录。';
      uncertain.append(div);
    }
    for (const item of items) {
      const div = document.createElement('div');
      div.textContent = '· ' + item.text + '（' + item.kind + '，' + item.status + '）';
      uncertain.append(div);
    }

    const notice = $('or-notice');
    notice.replaceChildren();
    const lines = [
      '原页影像是扫描原件，判断原文以此为准。',
      '“已校对原文”是逐页视觉转录并放大复核的结果，分隔线等装饰细节可能与原件略有出入。',
      '“配套解释”与自编练习单独标注，不混作原书内容。',
      state.manifest?.notice || ''
    ].filter(Boolean);
    for (const text of lines) {
      const div = document.createElement('div');
      div.textContent = '· ' + text;
      notice.append(div);
    }
  }

  async function renderText() {
    const article = $('or-text');
    article.replaceChildren();
    article.hidden = false;
    $('or-img').closest('figure').hidden = true;
    const request = ++state.textRequest;
    article.textContent = '正在读取已校对原文…';
    try {
      const response = await fetch('/api/original/text/' + state.page);
      if (!response.ok) throw new Error('原文读取失败（' + response.status + '）');
      const payload = await response.json();
      if (request !== state.textRequest) return;
      if (!payload.published) {
        article.textContent = '本页尚未识别校对，只提供原页影像。切回“原页影像”即可阅读原件。';
        return;
      }
      const markdown = String(payload.reviewed || '').replace(/\]\((?!https?:|\/)([^)]+\.png)\)/g, '](/api/original/figure/$1)');
      const ok = window.BookReader?.render(article, markdown, 'cpp/roberts/original/pages/' + String(state.page).padStart(4, '0') + '.reviewed.md');
      if (!ok) {
        article.textContent = markdown;
        return;
      }
      article.querySelectorAll('a[href*="/api/original/figure/"]').forEach((anchor) => {
        const src = anchor.getAttribute('href');
        const caption = anchor.textContent.replace(/^查看图示：/, '');
        const figure = document.createElement('figure');
        const image = document.createElement('img');
        image.src = src;
        image.alt = caption;
        image.loading = 'lazy';
        const label = document.createElement('figcaption');
        label.textContent = caption;
        figure.append(image, label);
        const parent = anchor.parentElement;
        if (parent && parent.tagName === 'P' && parent.children.length === 1
          && parent.textContent.trim() === anchor.textContent.trim()) {
          parent.replaceWith(figure);
        } else {
          anchor.replaceWith(figure);
        }
      });
    } catch (error) {
      if (request !== state.textRequest) return;
      article.textContent = error.message;
    }
  }

  function renderMode() {
    const isImage = state.mode === 'image';
    $('or-tab-image').setAttribute('aria-selected', String(isImage));
    $('or-tab-text').setAttribute('aria-selected', String(!isImage));
    if (isImage) {
      $('or-text').hidden = true;
      $('or-img').closest('figure').hidden = false;
      renderImage();
    } else {
      renderText();
    }
  }

  function render(force) {
    $('or-status').classList.remove('show');
    $('or-page').value = String(state.page);
    $('or-prev').disabled = state.page <= 1;
    $('or-next').disabled = state.page >= TOTAL;
    $('or-pdf').href = '/books/cpp-roberts.pdf#page=' + state.page;
    const entry = entryFor(state.page);
    $('or-hint').textContent = entry ? '本页有已校对原文' : '本页仅原页影像';
    renderPanel();
    renderImage(force);
    if (state.mode === 'text') renderText();
    history.replaceState(null, '', '#page=' + state.page);
  }

  function go(page) {
    const next = clampPage(page);
    if (next === state.page) return;
    state.page = next;
    render(true);
    window.scrollTo({ top: 0, behavior: 'smooth' });
  }

  function bind() {
    $('or-prev').onclick = () => go(state.page - 1);
    $('or-next').onclick = () => go(state.page + 1);
    $('or-page').onchange = (event) => go(event.target.value);
    $('or-fit').onclick = () => {
      state.fit = true;
      renderImage(true);
      toast('已适合宽度');
    };
    const zoom = (delta) => {
      if (state.fit) {
        state.fit = false;
        state.zoom = 100;
      }
      state.zoom = Math.min(400, Math.max(50, state.zoom + delta));
      renderImage(true);
    };
    $('or-zoom-in').onclick = () => zoom(25);
    $('or-zoom-out').onclick = () => zoom(-25);
    $('or-tab-image').onclick = () => {
      state.mode = 'image';
      renderMode();
    };
    $('or-tab-text').onclick = () => {
      if (!entryFor(state.page)) {
        toast('本页尚未识别校对，只提供原页影像');
        return;
      }
      state.mode = 'text';
      renderMode();
    };
    $('or-theme').onclick = () => {
      const dark = document.documentElement.dataset.theme === 'dark';
      document.documentElement.dataset.theme = dark ? 'light' : 'dark';
      $('or-theme').textContent = dark ? '切换深色' : '切换浅色';
      try {
        localStorage.setItem('study-theme', dark ? 'light' : 'dark');
      } catch {}
    };
    document.addEventListener('keydown', (event) => {
      if (event.target instanceof HTMLInputElement) return;
      if (event.key === 'ArrowLeft') go(state.page - 1);
      if (event.key === 'ArrowRight') go(state.page + 1);
    });
  }

  async function start() {
    $('or-theme').textContent = document.documentElement.dataset.theme === 'dark' ? '切换浅色' : '切换深色';
    bind();
    try {
      const response = await fetch('/api/original/manifest');
      state.manifest = response.ok ? await response.json() : { pages: [], sections: [], links: {} };
    } catch {
      state.manifest = { pages: [], sections: [], links: {} };
    }
    if (!state.manifest.ready) {
      $('or-hint').textContent = '原书阅读数据尚未发布';
    }
    const fromHash = Number.parseInt((location.hash.match(/page=(\d+)/) || [])[1], 10);
    state.page = clampPage(Number.isFinite(fromHash) ? fromHash : DEFAULT_PAGE);
    render(true);
  }

  start();
})();
