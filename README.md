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

-l          'log'
            lists all tasks on single line (one line per day for calendar mode), separated by semicolons, without givings times.


