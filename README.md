# hindsight

a time-tracking program inspired by the clocking function of emacs' org-mode.

## table of contents
1. [overview](#overview)
2. [example](#example)
3. [commands](#commands)
4. [flags](#flags)
5. [installation/setup](#inst)

## overview

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
lines starting with # are commented  
everything after a # in a task name is commented

## example:
input file would look like this
```
[random stuff]
!!!start
2021_02_20,6
    0930 wake
    1759-1821 school english
    2300-2341 books war and peace
    
2021_02_21,7
    1143 wake
    1100-1202 school math
    1309-1332 bigproject part 1
    1814-1827 bigproject part 2
    1831-1836 school english
    2145-2206 books a farewell to arms
    2300-0019 bigproject part 3, 4
    # this is a comment

2021_02_22,1
    0327 wake
    2228-2258 bigproject part 5
!!!end
[random stuff]
```

output would look like this
```
--------------------------------------------------------------------------------
> c
2021-02-20,sat
        wake                 09:30

        school               00:22
        books                00:41

        SUM TOTAL            01:03

2021-02-21,sun
        wake                 11:43

        school               01:07
        bigproject           01:55
        books                00:21

        SUM TOTAL            03:23

2021-02-22,mon
        wake                 03:27

        bigproject           00:30

        SUM TOTAL            00:30

--------------------------------------------------------------------------------
> c -d
2021-02-20,sat
        wake                 09:30

        school english       00:22
        books war and peace  00:41

        SUM TOTAL            01:03

2021-02-21,sun
        wake                 11:43

        school math          01:02
        bigproject part 1    00:23
        bigproject part 2    00:13
        school english       00:05
        books a farewell to arms 00:21
        bigproject part 3, 4 01:19

        SUM TOTAL            03:23

2021-02-22,mon
        wake                 03:27

        bigproject part 5    00:30

        SUM TOTAL            00:30

--------------------------------------------------------------------------------
> c -dl
2021-02-20,sat: school english; books war and peace;
2021-02-21,sun: school math; bigproject part 1; bigproject part 2; school english; books a farewell to arms; bigproject part 3, 4;
2021-02-22,mon: bigproject part 5;
--------------------------------------------------------------------------------
> s
        wake                 09:30

        school               01:29
        books                01:02
        bigproject           02:25

        SUM TOTAL            04:56

--------------------------------------------------------------------------------
> s -s
        wake                 09:30

        bigproject           02:25
        school               01:29
        books                01:02

        SUM TOTAL            04:56

--------------------------------------------------------------------------------
> s -dl
 school english; books war and peace; school math; bigproject part 1; bigproject part 2; books a farewell to arms; bigproject part 3, 4; bigproject part 5;
```

personally i like to put future days after !!!end, like an agenda, and then move them up when the time comes.
```
!!!start
[past days]

2021_02_22,1
    1040 wake
    2228-2258 climbtree

!!!end

2021_02_23,2 tree climbing exam
2021_02_24,3 SAT exam; AP exam
2021_02_25,4 ACT exam
2021_02_26,5 bar exam
2021_02_27,6 driving exam
2021_02_28,7 exam exam
[etc.]
```

## commands:  
(h)elp      help  
(s)um       summarize activity between two dates  
(c)al       summarize activity by day  
(q)uit      quit, duh  
(r)eread    reread file, also updates current day

## flags:  
-d          be detailed  
            undetaied task tracking treats the first space-separated word after a time range/instant as the name of the task.  
            detailed task tracking treats rest of the line after a time range/instant as the name of the task.  

-s          sort by time  
            sorts activities (not instants) by time spent, descending order.

-S          sort by name  
            sorts activities (not instants) by their names alphabetically

-l          log  
            lists all tasks on single line (one line per day for calendar mode), separated by semicolons, without giving times.

-p "\<pat\>"  pattern  
            lists only tasks/instants starting with \<pat\>. regex is not yet supported, however

## installation/setup:<a name="inst"></a>  
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
