### Valgrind:
`valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind.supp --gen-suppressions=all --track-fds=yes ./minishell`

# Leaks
```
n43:/tests$ exit
n43:/tests$ exit
==1096262== 
==1096262== FILE DESCRIPTORS: 7 open (3 std) at exit.
==1096262== Open file descriptor 6:
==1096262==    at 0x49E0EBD: pipe (pipe.c:29)
==1096262==    by 0x10BCB2: fill_in_cmd (init_cmd.c:79)
==1096262==    by 0x10BD3E: fill_cmd (init_cmd.c:98)
==1096262==    by 0x10C4FF: shell_loop2 (shell.c:41)
==1096262==    by 0x10C5AB: shell_loop (shell.c:63)
==1096262==    by 0x109657: main (main.c:123)
==1096262== 
==1096262== Open file descriptor 5:
==1096262==    at 0x49E0EBD: pipe (pipe.c:29)
==1096262==    by 0x10BCB2: fill_in_cmd (init_cmd.c:79)
==1096262==    by 0x10BD3E: fill_cmd (init_cmd.c:98)
==1096262==    by 0x10C4FF: shell_loop2 (shell.c:41)
==1096262==    by 0x10C5AB: shell_loop (shell.c:63)
==1096262==    by 0x109657: main (main.c:123)
==1096262== 
==1096262== Open file descriptor 4:
==1096262==    at 0x49E0EBD: pipe (pipe.c:29)
==1096262==    by 0x10BCB2: fill_in_cmd (init_cmd.c:79)
==1096262==    by 0x10BD3E: fill_cmd (init_cmd.c:98)
==1096262==    by 0x10C4FF: shell_loop2 (shell.c:41)
==1096262==    by 0x10C5AB: shell_loop (shell.c:63)
==1096262==    by 0x109657: main (main.c:123)
==1096262== 
==1096262== Open file descriptor 3:
==1096262==    at 0x49E0EBD: pipe (pipe.c:29)
==1096262==    by 0x10BCB2: fill_in_cmd (init_cmd.c:79)
==1096262==    by 0x10BD3E: fill_cmd (init_cmd.c:98)
==1096262==    by 0x10C4FF: shell_loop2 (shell.c:41)
==1096262==    by 0x10C5AB: shell_loop (shell.c:63)
==1096262==    by 0x109657: main (main.c:123)

=> des fd toujours ouver a l'exit
```

```
HEAP SUMMARY:
==1096262==     in use at exit: 241,465 bytes in 258 blocks
==1096262==   total heap usage: 3,150 allocs, 2,892 frees, 423,619 bytes allocated
==1096262== 
==1096262== 5 bytes in 1 blocks are still reachable in loss record 1 of 87
==1096262==    at 0x4841828: malloc (vg_replace_malloc.c:442)
==1096262==    by 0x10E712: malloc_tokens_utils (malloc_tokens.c:83)
==1096262==    by 0x10E7DA: malloc_tokens (malloc_tokens.c:104)
==1096262==    by 0x10A5A7: shell_split_tokens (tokens_split.c:116)
==1096262==    by 0x10C56F: shell_loop (shell.c:60)
==1096262==    by 0x109657: main (main.c:123)
```

```
==1096262== 5 bytes in 1 blocks are still reachable in loss record 2 of 87
==1096262==    at 0x4841828: malloc (vg_replace_malloc.c:442)
==1096262==    by 0x10A61C: ft_strdup (utils.c:23)
==1096262==    by 0x10BACF: fill_in_cmd (init_cmd.c:66)
==1096262==    by 0x10BD3E: fill_cmd (init_cmd.c:98)
==1096262==    by 0x10C4FF: shell_loop2 (shell.c:41)
==1096262==    by 0x10C5AB: shell_loop (shell.c:63)
==1096262==    by 0x109657: main (main.c:123)
==1096262==
```

## Tests
- [x] #task `export TEST="coucou" && echo $TEST` ✅ 2024-01-15
- [ ] #task `<<test`  (just its sending a `'' command not found`, but not the real bash)
```
n43:/tests$ "te$?st"
te0st: No such file or directory
n43:/tests$ "te$?st"
te0st: No such file or directory  -> status code devrai est a 127 apres le no such file or directory
```

- [x] #task `<<test'test                 'coucou` ✅ 2024-01-15
- [x] #task `<<test"coucou                         "test` ✅ 2024-01-15
- [x] #task `te$?st` => te0st ✅ 2024-01-15
- [x] #task `'te$?st'` => te$?st ✅ 2024-01-15
- [x] #task `"te$?st"` => te0st ✅ 2024-01-15
- [x] #task `'$HOME'` => `$HOME` ✅ 2024-01-15
- [ ] #task `"$HOME"` => /home/pioupia/
```
notre:
n43:/tests$ "$HOME"
/home/n43: Permission denied

bash;
[n43@rog tests]$ "$HOME"
bash: /home/n43 : est un dossier
```

- [x] #task `"'$HOME'"` => `'/home/pioupia/'` ✅ 2024-01-16
- [ ] #task `'"$HOME"'` => `"$HOME"`
```
bash:
[n43@rog tests]$ '"$HOME"'
bash: "$HOME" : commande introuvable => 127

n43:/tests$ '"$HOME"'
"$HOME": No such file or directory => 0
```

- [ ] #task `<< STOP cat < Makefile`
```
bash:
[n43@rog tests]$ << STOP cat < Makefile
> haha
> STOP
Makefile of unit_tests[n43@rog tests]$

nous:
n43:/tests$ << STOP cat < Makefile
>pl
>STOP
cat: erreur d'écriture: Mauvais descripteur de fichier
```

- [x] #task `<< STOP cat << TEST` ✅ 2024-01-16
- [ ] #task `cat < test.txt < README.md < test.txt  -e`  
```
bash:
[n43@rog tests]$ cat < test.txt < README.md < test.txt  -e
test.txt file in test folder$

nous:
n43:/tests$ cat < test.txt < README.md < test.txt  -e
test.txt file in test folder  => il manque le -e
```

- [ ] #task `cat -e test.txt > salut test > coucou > bjr` (with test file doesn't exist)  
```
bash:
[n43@rog tests]$ cat -e test.txt > salut test > coucou > bjr
cat: test: Aucun fichier ou dossier de ce type

nous:

```

- [x] #task `cat -e test.txt > salut > coucou > bjr` ✅ 2024-01-16
- [ ] #task `cd -` (do not manage)
```
pas gerer
```

- [ ] #task `cd ~` (do not mamage)
```
pas gerer
```

- [ ] #task `<> world` will create the world file  
```
<> world ne cree pas le fichier alors que bash le cree
```

- [ ] #task `<> world cat -e` will open the world file, read it, send its content into the cat command. But the original file is not modified. 
```
bash:
[n43@rog tests]$ <> world cat -e
[n43@rog tests]$ cat world 
[n43@rog tests]$ echo "plop" > world 
[n43@rog tests]$ <> world cat -e
plop$

nous:
n43:/tests$ <> world cat -e
plop$
n43:/tests$ rm world 
n43:/tests$ <> world cat -e
minishell: No such file or directory
```

- [ ] #task `1<> world cat` will edit the content of the world file, and wait the read of the `cat` command...
```
bash:
[n43@rog tests]$ 1<> world cat
haha     ==> CTRL + D
[n43@rog tests]$ cat world 
haha

nous:
n43:/tests$ 1<> world cat
1: No such file or directory
```

- [ ] #task `echo "test" <> world` will echo in the console then create the world file.
```
tjrs le meme probleme, le fichier n'est pas creer
```

- [ ] #task `echo "test" 1<> world` will print nothing but will write `test` in the world file.
```
tjrs le meme probleme, le fichier n'est pas creer
```

- [ ] #task `'' "$HOME"`  (its sending `/home/pioupia` command not found, but it should print `''` command not found)
```
bash:
[n43@rog tests]$ '' "$HOME"
bash:  : commande introuvable

nous:
n43:/tests$ '' "$HOME"
Permission denied
```

- [ ] #task `'' '$HOME'` 
```
bash:
[n43@rog tests]$ '' '$HOME'
bash:  : commande introuvable

nous:
n43:/tests$ '' '$HOME'
Permission denied
```

- [ ] #task `'' $HOME` 
```
bash:
[n43@rog tests]$ '' $HOME
bash:  : commande introuvable

nous:
n43:/tests$ '' $HOME
Permission denied
```

- [ ] #task `>> bonjour` => create a `bonjour` file  
```
n43:/tests$ >> bonjour
>>: No such file or directory
```

- [ ] #task ` $HOME"TEST"`  
```
bash:
[n43@rog tests]$ $HOME"TEST"
bash: /home/n43TEST: Aucun fichier ou dossier de ce type

nous:
n43:/tests$ $HOME"TEST"
n43:/tests$
```

- [ ] #task `export PATH="" && ls` => command not found 
```
n43:/tests$ export PATH=""
n43:/tests$ ls
ls: No such file or directory
```

- [ ] #task `echo "test" 8192> coucou` => `bash: 8192: Bad file descriptor` :x:
```
bash:
[n43@rog tests]$ echo "test" 8192> coucou
bash: 8192: Mauvais descripteur de fichier

nous:
n43:/tests$ echo "test" 8192> coucou
n43:/tests$ cat coucou 
test 8192
```
- [x] #task `echo "test" -1> coucou` => no output -> write `test -1\n` in the `coucou` file. :x: ✅ 2024-01-16
- [x] #task `cat | cat | cat | ls` => `ls` should be executed before all cat. ✅ 2024-01-16
- [x] #task `<< lim << lim << lim << lim | cat > out` => open swa ouvre tt les heredoc mais out ne recoit rien, bash fait la meme chose ✅ 2024-01-16
- [ ] #task `cat | asdoijasiod` => send `error not found` then the return code is 127  
```
bash:
[n43@rog tests]$ cat | asdoijasiod
bash: asdoijasiod : commande introuvable
[n43@rog tests]$ echo $?
127

nous:
n43:/tests$ cat | asdoijasiod
asdoijasiod: No such file or directory
n43:/tests$ echo $?
0
```

- [x] #task `export TEST="coucou===Commenttuvas?" && ./minishell` => the env variable TEST should be well formated. ✅ 2024-01-16
- [ ] #task `<< "$HOME test"coucou`  
```
bash :
n43@rog tests]$ << "$HOME test"coucou
> plop
> $HOME testcoucou
[n43@rog tests]$

nous:
n43:/tests$ << "$HOME test"coucou
>plop
>$HOME testcoucou
>
```

- [ ] #task `"" cat` 
```
bash:
[n43@rog tests]$ "" cat
bash:  : commande introuvable

nous:
n43:/tests$ "" cat
Permission denied
```

- [ ] #task ` << "" "" cat`  
```
bash:
[n43@rog tests]$ << "" "" cat
> 
bash:  : commande introuvable

nous:
n43:/tests$ << "" "" cat
>
Permission denied
```

- [ ] #task `./ls` were `ls` does not exists in the current dir.  (send too many errors)
```
bash:
[n43@rog tests]$ ./ls
bash: ./ls: Aucun fichier ou dossier de ce type
[n43@rog tests]$ echo $?
127

nous:
n43:/tests$ ./ls
n43:/tests$
n43:/tests$ echo $?
2
```

- [x] #task `test` where test is an executable in the current directory ✅ 2024-01-16
- [ ] #task ` << LIM < tset < salut cat | cat < file > output | asdjaisj <>world | > a > b > c > d > e` 
```
bash:
[n43@rog tests]$ << LIM < tset < salut cat | cat < file > output | asdjaisj <>world | > a > b > c > d > e
1
LIM
bash: file: Aucun fichier ou dossier de ce type
bash: asdjaisj : commande introuvable
bash: tset: Aucun fichier ou dossier de ce type

nous:
n43:/tests$ << LIM < tset < salut cat | cat < file > output | asdjaisj <>world | > a > b > c > d > e
>1
>LIM
n43:/tests$
```

- [ ] #task ` cat -e Makefile| > a > b > c > d > e`  
```
nous:
n43:/tests$ cat -e Makefile| > a > b > c > d > e
>: No such file or directory
```
- [ ] #task `cat < Makefile > out`  send the Makefile content into the outfile
```
bash:
[n43@rog tests]$ cat < Makefile > out
[n43@rog tests]$ cat out
Makefile of unit_tests[n43@rog tests]$

nous:
n43:/tests$ cat < Makefile > out

=> sa hang

n43:/tests$ cat out


n43:/tests$
```
- [ ] #task `> out`  (reset the out file)
- [ ] #task `<< LIM < test < coucou < salut`    (working but should exit with `1` as status code - don't because of the input file crash).
- [ ] #task `cat "$TEST"*'.md'` => with one or many md files :x:
- [ ] #task `make*` => work with one file  
- [ ] #task `make*` if we have a file named `make` and a file named `makecoucou`, the file named `makecoucou` will be set in the args array. 
- [ ] #task `cat < make*` => with one file were its name starts by `make` it'll work. If we have multiple files, that just not working and send an error `bash: make*: ambiguous redirect`  
- [ ] #task :warning: The wildcard works with directory.
- [ ] #task `(cat M*k*)` 
- [ ] #task `cat -e < make* | iadoiausidasdoudo` with ambigous redirection (should print `iadoi... command not found`) 
- [ ] #task `cat -e < "$PWD"/make*` :x:
- [ ] #task `(echo 1 && echo 2) | cat`  
- [ ] #task `cat Makefile | aisdaisdiasdij | cat -e README.md`  
- [ ] #task `asuidhausid | echo $? | aoisdjiasd | echo $? | echo $? | asdopjasd` will just print errors  
- [ ] #task `cat | cat | ls > sss || $?`  
- [ ] #task `export PATH=` => has to refresh the parse array in the minishell struct.  

`Injecting env variable before the launch of the minishell.`
- [ ] #task `export TEST="coucou=salut"`  
`then run the minishell and run:``
- [ ] #task `echo $TEST`  
- [ ] #task `exit -2500000` => exit code 96  
- [ ] #task `exit -23974` => exit code 90  
- [ ] #task `exit 42564` => exit code 68  
- [ ] #task `exit test` => exit code 2 + stderr: `exit\nbash: exit: test: numeric argument required`  
- [ ] #task `exit 0 test` => don't exit + stderr: `exit\nbash: exit: too many arguments`  
- [ ] #task `cd` => go to the `$HOME` location  
- [ ] #task `unset HOME && cd` => stderror: `bash: cd: HOME not set` ; status: `1` ; the directory don't move 
- [ ] #task `unset HOME && export HOME && cd` => stderror: `bash: cd: HOME not set` ; status: `1` ; the directory don't move 
- [ ] #task `unset HOME && export HOME= && cd` => status: `0` ; the directory don't move 
- [ ] #task `export HOME=/home/pioupia/unexisting_path && cd` => stderr: `bash: cd: /home/pioupia/unexisting_path: No such file or directory` ; status `1` ; directory don't move 
- [ ] #task `export HOME=./libft && cd`  => change the directory to the local libft dir. 
- [ ] #task `echo 1 || echo 2 | echo 3 | echo 4 || echo 10 || echo 100` => ça echo `1\n` 
- [ ] #task `asdhaosid || echo 2 | echo 3 | echo 4 || echo 10 || echo 100` => ça echo `asdhaosid: command not found` (stderr) + `4` sur une nouvelle ligne. 
- [ ] #task `echo 1 || echo 2 && echo 3` => echo `1`, `3` 
- [ ] #task `echo 3 && aposjdaopsd || echo 2` => echo `3`, `aposjdaopsd: command not found`, `2` 
- [ ] #task `echo 3 && echo 1 || echo 2` => echo `3`, `1` 
- [ ] #task `cat | cat | ls || echo 1` => `cat | cat | ls` normal 
- [ ] #task `cat | cat | ls && echo 1` => `cat | cat | ls` normal mais `1\n` à la fin. 
- [ ] #task `echo 1 || echo 2 && echo 3` => should print `1` and `3` on a new line 
- [ ] #task `echo 1 || (echo 2 && echo 3)` => should print `1` followed by a new line 
- [ ] #task `asdojasoidhaiosdh && (echo 1 || echo 2)` => just an error 
- [ ] #task `asdojasoidhaiosdh && echo 1 || echo 2` => error + echo 2 
- [ ] #task `<< LIM ''` => take the limiter and `command not found`  ; status `127`
- [ ] #task `<< LIM` => only take the limiter without errors   ; status `1`
- [ ] #task `<< '' cat` => should not print any errors 
- [ ] #task `echo expr $? + $?` => should print `expr 0 + 0` 
- [ ] #task `echo '' test '' salut '' '' '' '' '' coucou` should print ` test  salut      coucou`
- [ ] #task `ca"$TEST"t` if the $TEST variable doesn't exist, this should execute the `cat` command.
- [ ] #task 
- [ ] #task Should execute the `echo` command:
- [ ] #task ```
- [ ] #task export H="echo "
- [ ] #task $H salut
- [ ] #task ```
- [ ] #task 
- [ ] #task `$TEST cat -e Makefile` should print the Makefile if the `TEST` variable does not exist.

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