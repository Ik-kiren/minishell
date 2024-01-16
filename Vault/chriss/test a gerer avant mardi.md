# check tdes commantaires:

## exit

```
- gerer les long overflow
- gerer les status code
- gerer les affichages des erreur
```

## echo

```
- echo ne change pas le status code
ls -l  a
```
![image](https://github.com/Ik-kiren/minishell/assets/80333328/fbadd5a1-6f49-4a5e-a60a-47109a7b57ac)
![image](https://github.com/Ik-kiren/minishell/assets/80333328/95a468f8-9b63-4ca5-8127-ed69a87721f9)
![image](https://github.com/Ik-kiren/minishell/assets/80333328/c49919f5-befc-4192-b87e-a86f997f3326)

## heredoc

> probleme de dup2 avec plusieur file in, file out
> chech leak aleatoire ctrl + D

## env

>renvoi pid quand $$

# execve
> unset path : si commence par / pas faire de check acces avec len env mais uniquement avec le pat absolu
>              si commence par . utilise getcwd pour le remplacer dans la commande

# redirectionecho 
> redirection infile pas d'erreur access, execution malgré fichier qui n'existe pas
> verifier les status code des verification access
> access avec chemin absolue et ./
