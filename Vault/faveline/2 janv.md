
Fait : int ok a faire pdt les dup/execve (sinon prb quand cmd1 ok mais cmd2 pas ok) 

< command vraiment une bnne idee ? a discuter

Fait : Modif sur freee et sur cmd_clear et ajout de a->g dans la fct cmd_argument.

gerer les parentheses (pour le moment les par sont considerees comme des cmds)

Fait : Retrait de plein de fct obsoletes 

finir avec && || |   ---> ordre a faire
Fait : finir avec " (voir avec David)

test avec :
test -u file1 && test2 file3 > file4 | test3 < file1 file5

error | correct -> print result then error
error || correct -> print error then result

refaire a 0 en changeant l'idee | = || -> traiter les pipes a part et relancer le programme pour chaque && ou ||

ft_do_cmd a proteger (dup2 et execve)