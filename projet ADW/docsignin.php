<?php
	session_start();
	// à compléter
	// Dans cette partie, on teste le login et le mot de passe :
	// - on teste si le login proposé existe bien 
	// - on teste si le mot de passe correspond
	// En cas de succès :
	// - si le paramètre "goto" existe, on redirige l'utilisateur vers le script
	//   qui est la valeur de ce paramètre
	// - sinon on redirige l'utilisateur vers "page1.php"
	// En cas d'échec, on redirige l'utilisateur vers la page de login
	function test($l,$m,$csv){
		foreach(file($csv, FILE_IGNORE_NEW_LINES) as $line){
			$tokens = explode(',',$line);
			if ($tokens[0]==$l && $tokens[1]==md5($m)){
				return true;
			}
		}
		return false;
	}
	$file="users.csv";
	echo "lalala";
	if(isset($_POST['Nouvelle inscription'])){
		header("Location: signup.php");
			exit();
	}
	if(isset($_POST['login']) && isset($_POST['password']) && test($_POST['login'],$_POST['password'],$file)){
			$_SESSION["login"] = $_POST['login'];
			if(isset($_GET["goto"])){
				header("Location: ".$_GET["goto"]);	//ouvrir page1
				exit();
			}
			header("Location: formulaire.php");	//ouvrir page1
			exit();
	}
	else{
		header("Location: signin.php?badlogin=bad");	//remettre signin
		exit();
	}

?>
