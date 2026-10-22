#!/usr/bin/env bash
set -eu
sandbox=$1
script=$2
case "$sandbox" in /mnt/d/Book-Learning/linux/sandbox/*) ;; *) echo 'Unexpected sandbox' >&2; exit 2;; esac
case "$script" in /mnt/d/Book-Learning/linux/chapters/*.sh|/mnt/d/Book-Learning/linux/projects/*.sh) ;; *) echo 'Unexpected script' >&2; exit 2;; esac
cd -- "$sandbox"
exec bash "$script"
