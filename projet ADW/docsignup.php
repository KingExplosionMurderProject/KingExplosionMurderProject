<?php
	$users = file("fichiersCVS/users.csv",FILE_IGNORE_NEW_LINES);
	$login = $_POST[ "login" ];
	$mdp1 = $_POST[ "password1" ];
	$mdp2 = $_POST[ "password2" ];
    $type = $_POST["type"];
	
	if ( ! preg_match("/^[a-zA-Z]+$/", $login) ) //si il y a un élément qui n'est pas une lettre, renvoie une erreur
	{
		header("Location: signup.php?badsignup=1");
		die();
	}
	
	$found = false;
	
	foreach ( $users as $line ) //on va regarder chaque utilisateur déjà inscript
	{
		$a = explode(",",$line);
		if ( $login == $a[0] )
		{
			$found = true;
			break;
		}
	}
	
	if ( $found ) //si l'utilisateur existe déja, renvoie un message d'erreur
	{
		header("Location: signup.php?badsignup=2");
		die();
	}
	
	if ( strlen( $mdp1 ) < 4 ) // si le mot de passe est trop court, renvoie un message d'erreur
	{
		header("Location: signup.php?badsignup=3");
		die();
	}
	
	if ( $mdp1 != $mdp2 ) // si le mot de passe et sa confirmation sont différents, renvoie une erreur
	{
		header("Location: signup.php?badsignup=4");
		die();
	}
	
	$users[] = "$login," . md5($mdp1).","."$type,"; // on créé l'utilisateur avec ses info pour le fichier
	$newcontent = join("\n", $users) . "\n";
	file_put_contents("users.csv", $newcontent); // on met le nouvel utilisateur dans le fichier
	header("Location: signin.php");

// rajouter dans le canaux.csv l'utilisateur (listes où il peut aller)

?>
