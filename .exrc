set makeprg=./make
autocmd BufEnter *.3mlib setf nroff
autocmd BufEnter README  set tw=73 et
autocmd BufEnter *Test   set tw=73 commentstring=#\ %s
