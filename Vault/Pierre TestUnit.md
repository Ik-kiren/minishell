### Valgrind:
`valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind.supp --gen-suppressions=all --track-fds=yes ./minishell`

### Tests
`export TEST="coucou" && echo $TEST`  
`<<test`  (just its sending a `'' command not found`, but not the real bash)
`<<test'test                 'coucou`  
`<<test"coucou                         "test`  
`te$?st` => te0st  
`'te$?st'` => te$?st  
`"te$?st"` => te0st  
`'$HOME'` => `$HOME`  
`"$HOME"` => /home/pioupia/  
`"'$HOME'"` => `'/home/pioupia/'`  
`'"$HOME"'` => `"$HOME"`  
`<< STOP cat < Makefile`  
`<< STOP cat << TEST`  
`cat < test.txt < README.md < test.txt  -e`  
`cat -e test.txt > salut test > coucou > bjr` (with test file doesn't exist)  
`cat -e test.txt > salut > coucou > bjr`  
`cd -` (do not manage)
`cd ~` (do not mamage)
`<> world` will create the world file  
`<> world cat -e` will open the world file, read it, send its content into the cat command. But the original file is not modified. :x:
`1<> world cat` will edit the content of the world file, and wait the read of the `cat` command...
`echo "test" <> world` will echo in the console then create the world file. :x:
`echo "test" 1<> world` will print nothing but will write `test` in the world file. :x:
`'' "$HOME"`  (its sending `/home/pioupia` command not found, but it should print `''` command not found)
`'' '$HOME'` 
`'' $HOME` 
`< *.h cat` => should return an error if multiple `.h` files, if just one file, thats working (should just print `ambigous redirection` and stop the command here)  
`< make* cat | cat -e Makefile`  
`cat parser.h > *.c` => Will create a `*.c` file if there is no .c file; if there are 2 .c files or more, it fails  
`>> bonjour` => create a `bonjour` file  
` $HOME"TEST"`  
`export PATH="" && ls` => command not found 
`echo "test" 8191> coucou` => working :x:
`echo "test" 8192> coucou` => `bash: 8192: Bad file descriptor` :x:
`echo "test" -1> coucou` => no output -> write `test -1\n` in the `coucou` file. :x:
`cat -e Makefile && << test cat`  
`cat | cat | cat | ls` => `ls` should be executed before all cat.
`<< lim << lim << lim << lim | cat > out` => open all lim but only send the content of the first lim to the cat command  
`cat | asdoijasiod` => send `error not found` then the return code is 127  
`export TEST="coucou===Commenttuvas?" && ./minishell` => the env variable TEST should be well formated.
`<< "$HOME test"coucou`  
`"" cat` 
` << "" "" cat`  
`./ls` were `ls` does not exists in the current dir.  (send too many errors)
`test` where test is an executable in the current directory 
` << LIM < tset < salut cat | cat < file > output | asdjaisj <>world | > a > b > c > d > e` :x:
` cat -e Makefile| > a > b > c > d > e`  
`cat < Makefile > out`  send the Makefile content into the outfile
`> out`  (reset the out file)
`<< LIM < test < coucou < salut`    (working but should exit with `1` as status code - don't because of the input file crash).
`cat "$TEST"*'.md'` => with one or many md files :x:
`make*` => work with one file  
`make*` if we have a file named `make` and a file named `makecoucou`, the file named `makecoucou` will be set in the args array. 
`cat < make*` => with one file were its name starts by `make` it'll work. If we have multiple files, that just not working and send an error `bash: make*: ambiguous redirect`  
:warning: The wildcard works with directory.
`(cat M*k*)` 
`cat -e < make* | iadoiausidasdoudo` with ambigous redirection (should print `iadoi... command not found`) 
`cat -e < "$PWD"/make*` :x:
`(echo 1 && echo 2) | cat`  
`cat Makefile | aisdaisdiasdij | cat -e README.md`  
`asuidhausid | echo $? | aoisdjiasd | echo $? | echo $? | asdopjasd` will just print errors  
`cat | cat | ls > sss || $?`  
`export PATH=` => has to refresh the parse array in the minishell struct.  
Injecting env variable before the launch of the minishell.
`export TEST="coucou=salut"`  
then run the minishell and run:
`echo $TEST`  
`exit -2500000` => exit code 96  
`exit -23974` => exit code 90  
`exit 42564` => exit code 68  
`exit test` => exit code 2 + stderr: `exit\nbash: exit: test: numeric argument required`  
`exit 0 test` => don't exit + stderr: `exit\nbash: exit: too many arguments`  
`cd` => go to the `$HOME` location  
`unset HOME && cd` => stderror: `bash: cd: HOME not set` ; status: `1` ; the directory don't move 
`unset HOME && export HOME && cd` => stderror: `bash: cd: HOME not set` ; status: `1` ; the directory don't move 
`unset HOME && export HOME= && cd` => status: `0` ; the directory don't move 
`export HOME=/home/pioupia/unexisting_path && cd` => stderr: `bash: cd: /home/pioupia/unexisting_path: No such file or directory` ; status `1` ; directory don't move 
`export HOME=./libft && cd`  => change the directory to the local libft dir. 
`echo 1 || echo 2 | echo 3 | echo 4 || echo 10 || echo 100` => ça echo `1\n` 
`asdhaosid || echo 2 | echo 3 | echo 4 || echo 10 || echo 100` => ça echo `asdhaosid: command not found` (stderr) + `4` sur une nouvelle ligne. 
`echo 1 || echo 2 && echo 3` => echo `1`, `3` 
`echo 3 && aposjdaopsd || echo 2` => echo `3`, `aposjdaopsd: command not found`, `2` 
`echo 3 && echo 1 || echo 2` => echo `3`, `1` 
`cat | cat | ls || echo 1` => `cat | cat | ls` normal 
`cat | cat | ls && echo 1` => `cat | cat | ls` normal mais `1\n` à la fin. 
`echo 1 || echo 2 && echo 3` => should print `1` and `3` on a new line 
`echo 1 || (echo 2 && echo 3)` => should print `1` followed by a new line 
`asdojasoidhaiosdh && (echo 1 || echo 2)` => just an error 
`asdojasoidhaiosdh && echo 1 || echo 2` => error + echo 2 
`<< LIM ''` => take the limiter and `command not found`  ; status `127`
`<< LIM` => only take the limiter without errors   ; status `1`
`<< '' cat` => should not print any errors 
`echo expr $? + $?` => should print `expr 0 + 0` 
`echo '' test '' salut '' '' '' '' '' coucou` should print ` test  salut      coucou`
`ca"$TEST"t` if the $TEST variable doesn't exist, this should execute the `cat` command.

Should execute the `echo` command:
```
export H="echo "
$H salut
```

`$TEST cat -e Makefile` should print the Makefile if the `TEST` variable does not exist.

should echo salut:
```
export A=e B=ch C=o
$A$B$C salut
```

`test.sh`:
```sh
while read line
do
  echo "$line"
done < "${1:-/dev/stdin}"
```
`./test.sh | ls` => will execute `ls` before `./test.sh`

`<< a )` => Has to take the here_doc before sending an error
`<< a (` => Has to take the here_doc before sending an error
`<< a ) && << b` => take only the first here_doc before error
`<< a ) << b` => take only the first here_doc before error

Redirections:
```
<< "$H"'T'*W
<< "              $H               "'                    T                               '*W
<< "              $H               "              '                    T                               '*W
<< "$H       test        "              '                    T                               '*W
<< "test  $H "              '                    T                               '*W
<< "test  $H test"              '                    T                               '*W
<< "$H"T *W
```
Try to `control + d`, `control + c` and `control + \` on the here_doc see how the real bash react.

Test Ikar :
- crash sur `echo -n` -> ne crash pas sur les pipe -> fork
- Signal interuption -> valeur de retour pas set en cas d'interuptioon (128 + valeur du signal)
- le parsing des `""` et des `''` se fait apres la verification des commandes -> `"ls"` ne marche pas, contrairement a son vrai commportement
- SHLVL: increment la variable plz
- export sans arguments -> j'aurais aimé les `decalre -x`
- malheureusement, vis-a-vis du pwd/cd/gestion de la variable PWD, il suit le lien symboliques de maniere physiques et pas logiques
	- ex: cd `$HOME/goinfre` puis `cd ..` ne place dans `/goinfre` et non pas dans `$HOME`
- :( les pipes on m'avait dit ils etaient bien et au final ils ont pas le bon comportement (tout les process en meme temps)
- les headers ! point III-6 de la 