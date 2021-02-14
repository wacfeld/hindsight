# hindsight
a time-tracking program inspired by the clocking function of emacs' org-mode.

the difference is that emacs list times under tasks, while this lists tasks next to times under days.
i think this is a nicer, cleaner way to list things.
therefore this program cannot track time periods across more than two days.
it can, however, track across two days, to track things happening around midnight.

TLDR hindsight is way less powerful than org-mode, but i like it more.
that's why i made it.

also this project is not finished, so the info below is not all correct.

date format: yyyy\_mm\_dd or yyyy-mm-dd  
time range (activity) format: hhmm-hhmm or hhmm\_hhmm, time instant format hhmm  
command format: <mode> \[date1\] \[date2\] \[slags\]  
time format hhmm  
lines starting with # are commented.  
everything after a # in a task name is commented

run in command line with "./hindsight <filename>"

commands:  
(h)elp      help  
(s)um       summarize activity between two dates  
s(p)ec      summarize certain activity between two dates  
(c)al       summarize activity by day  
(q)uit      quit, duh  
(r)eread    reread file, also updates current day

flags:  
-d          be detailed  
            undetaied task tracking treats the first space-separated word after a time range/instant as the name of the task.  
            detailed task tracking treats rest of the line after a time range/instant as the name of the task.  

-s          sort  
            sorts activities (not instants) by time spent, descending order.

-l          log  
            lists all tasks on single line (one line per day for calendar mode), separated by semicolons, without giving times.

installation/setup:  
`cc main.c -o hsight` to install.  
`/path/to/hsight hindsight.txt` to run.  
format `hindsight.txt` as described above. everything before `!!!start` and after `!!!end` (by themselves on one line) in the file is ignored.  

personally i use vim, so i also have the below mappings to facilitate use:  
```
nnoremap <silent> <leader>h :e /path/to/hindsight.txt<cr>gg/!!!end<cr>:nohl<cr>  
nnoremap <silent> <leader>H :e /path/to/hindsight.txt<cr>gg/!!!end<cr>:nohl<cr>:term<cr><c-w>Lrlwrap /path/to/hsight /path/to/hindsight.txt<cr>  
```
the first one opens `hindsight.txt` and navigates to the latest date. the second one does the same, then opens a terminal alongside that and runs `hsight`.

i also use these for time/date insertion:
```
inoremap <silent> <f3> <C-R>=strftime("%F,%a")<CR><esc>hh~la
cnoremap <f3> <C-R>=strftime("%F,%a")<CR>
nnoremap <silent> <f3> i<C-R>=strftime("%F,%a")<CR><esc>hh~ll

inoremap <silent> <S-f3> <C-r>=strftime("%H%M")<CR>
cnoremap <S-f3> <C-r>=strftime("%H%M")<CR>
nnoremap <silent> <S-f3> i<C-r>=strftime("%H%M")<CR><esc>l

nnoremap <silent> <m-s-f3> 4s<C-r>=strftime("%H%M")<CR><esc>3h

nnoremap <silent> <m-f3> 14s<C-R>=strftime("%F,%a")<CR><esc>hh~ll
```
these insert the date, insert the time, and replace the date/time, respectively, in various modes.
