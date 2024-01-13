# David

- [x] #task 1- Ajout du garbage collector ✅ 2023-12-18
- [x] #task 2- tu peux tester par exemple:   <file1   X  < file2   > file8    >   file9 (X etant la commande ,si X n'est pas un fichier/executable, cmds->ok passe a -1.) ✅ 2023-12-16
- [x] #task 3- modification du garbage ➕ 2023-12-17 ✅ 2023-12-17
- [x] #task 4- env (ajout de print_env et de env_get_path) ➕ 2023-12-17 ✅ 2023-12-17
- [x] #task 5- ajoute du builtin env ➕ 2023-12-17 ✅ 2023-12-17
- [x] #task 6- ajout d' exec basique ➕ 2023-12-18 ✅ 2023-12-18
- [x] #task 7- check all malloc fail and exit corect way ⏫ ➕ 2023-12-18
- [x] #task 8- first implementation of exec ➕ 2023-12-18 ✅ 2023-12-18
- [x] #task 9- ajout de envs_to_array && refactorisation de exec dans une fonction do_exec ➕ 2023-12-18 ✅ 2023-12-18
- [ ] #task 10-dissocier les exec des builtin des autres (built in > pipes et dup2 mais pas de fork ni de execve) ➕ 2023-12-18
- [x] #task 11-inscrire les pid dans le tableaux de pid et les waitpid dans l'ordre ou il on ete lancer ➕ 2023-12-18
- [x] #task 12-gerer les bug de debogage ➕ 2023-12-18
- [ ] #task 13-gerer les not found in path pour les builtins

## details

##### task 1
```c
int	main(void)
{
	t_args		a;
	// t_cmd		*tmp;
	// t_cmd		*tmp2;
	
	init_args(&a);
	
	// test garbage collector
	// char *ptr1 = mallocc(a.g, sizeof(char) * 42);
	// int *ptr2 = mallocc(a.g, sizeof(int) * 42);
	// char *ptr3 = mallocc(a.g, sizeof(char *) * 42);

	// char *arg1 = mallocc(a.g, sizeof(char) * 42);
	// char *arg2 = mallocc(a.g, sizeof(char) * 42);
	// freee(a.g, ptr2);


	// ft_strlcpy(ptr1, "cat", 42);
	// ft_strlcpy(ptr3, "ls", 42);
	// ft_strlcpy(arg1, "arg1.1", 42);
	// ft_strlcpy(ptr3, "arg1.2", 42);

	// tmp = cmd_new(ptr1);
	// cmd_arg_add_back(&(tmp->args), cmd_arg_new(arg1));
	// tmp->name = "coucou-1";
	// cmd_add_back(&a, tmp);
	// tmp2 = cmd_new(ptr3);
	// cmd_arg_add_back(&(tmp2->args), cmd_arg_new(arg2));
	// tmp2->name = "coucou-2";
	// cmd_add_back(&a, tmp2);
	// cmd_del_one(&a, "coucou-1");
	// cmd_clear_all(&a);

	// free_all(a.g);
	if (ft_read_prompt(&a) < 0)
	{
		free_all(a.g);
		return (ft_exterminate(&a),  1);
	}
	free_all(a.g);
	return (0);
}
```

##### task 2
![](Pasted%20image%2020231216073253.png)

> ta fonction fonctionne correctement avec des > < par contre on a un heap overflow sans:

![](Pasted%20image%2020231216073533.png)


##### task 3
```c
a->g = garbage_init();  // initialisation du garbage collector
print_garbage(a.g);     // affichage du contenu du garbage en dehors du mode debug
garbage_free_all(a.g);  // destroy all ptr allocated by mallocc and all elem of the list
print_garbage(a.g);
garbage_destroy(a.g);   // free du garbage collector (premier maillon de la liste qui ne contient pas de pointeur aloue)
```

##### task 4

###### print_env
> print env fonctionne uniquement en mode debug

```c
print_env(&a);
```
![](Pasted%20image%2020231217065702.png)

![](Pasted%20image%2020231217092100.png)
###### env_get_path

```
ft_printf("PATH=%s\n", env_get_path(&a));
```

![](Pasted%20image%2020231217065542.png)




##### task 5
![](Pasted%20image%2020231217091923.png)




##### task 6

```c
	lst = cmd_new(&a, ft_g_strdup(a.g, "/usr/bin/cat"));
	cmd_arg_add_back(&(lst->args), \
		cmd_arg_new(ft_g_strdup(a.g, "tests/file1")));
	lst->name = "cat-1";
	lst->order = 0;
	cmd_add_back(&a, lst);
	lst = cmd_new(&a, ft_g_strdup(a.g, "/usr/bin/wc"));
	cmd_arg_add_back(&(lst->args), cmd_arg_new(ft_g_strdup(a.g, "-l")));
	lst->name = "wc-2";
	lst->order = 1;
	cmd_add_back(&a, lst);

	create_pipes(&a);

	a.i = -1;
	while (++(a.i), a.i < a.nbr_cmd_elem)
		do_fork(&a, cmg_get_by_order(&a, a.i), envp);
	close_pipes(&a);
	waitpid(-1, NULL, 0);
```
![](Pasted%20image%2020231218061056.png)
##### task 8
```
	lst = cmd_new(&a, ft_g_strdup(a.g, "/usr/bin/cat"));
	cmd_arg_add_back(&(lst->args), \
		cmd_arg_new(ft_g_strdup(a.g, "tests/file1")));
	lst->name = "cat-1";
	lst->order = 0;
	cmd_add_back(&a, lst);
	lst = cmd_new(&a, ft_g_strdup(a.g, "/usr/bin/wc"));
	cmd_arg_add_back(&(lst->args), cmd_arg_new(ft_g_strdup(a.g, "-l")));
	lst->name = "wc-2";
	lst->order = 1;
	cmd_add_back(&a, lst);

	create_pipes(&a);

	a.i = -1;
	while (++(a.i), a.i < a.nbr_cmd_elem)
		do_fork(&a, cmg_get_by_order(&a, a.i), envp);
	close_pipes(&a);
	waitpid(-1, NULL, 0);
```
![](Pasted%20image%2020231218052238.png)


##### task 12
```c
	// cmd_clear_all(&a);
	//garbage_free_all(a.g);
	//garbage_destroy(a.g);
```
##### task 13
![](Pasted%20image%2020240108080749.png)
