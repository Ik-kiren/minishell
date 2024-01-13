![](Pasted%20image%2020231215162933.png)
j'ai change le malloc en mallocc lors de la creation de la liste pour mieux la free

![](Pasted%20image%2020231215163842.png)
j'ai rajoute le free de la garbage list

![](Pasted%20image%2020231215172030.png)
Il reste un dernier leak quand les fonctions du type ft_strjoin sont utilisees, on peut mallocc une copie du resultat et free le resultat, c'est surement plus simple que de modif ta libft

![](Pasted%20image%2020231215172350.png)
j'ai aussi ajoute plusieurs fichiers pour mieux pouvoir normer les fonctions des redirections (+ quelques modifs sur ces fct), enocre BCP de boulot sur ces fct

J'ai creer des fonction find_cmd pour mallocc et remplir a->cmds->cmd
(dans le file ft_init_cmds.c)
tu peux tester par exemple:   <file1   X  < file2   > file8    >   file9
X etant la commande ,si X n'est pas un fichier/executable, cmds->ok passe a -1.

La norminette devient folle parce que j'ai pas bien config mon vscode, du coup elle pense que mes tab sont des espaces... CATASTROPHE

je reviens demain aprem a+