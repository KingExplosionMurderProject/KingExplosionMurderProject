<?php
// Ici, on va définir correctement la variable $action utilisée plus bas :
// si on passe le paramètre "goto" au script, l'action doit être "dosignin.php" avec ce même paramètre "goto"
// sinon l'action doit être le script "goto" sans paramètre
session_start();

if (isset($_SESSION['login'])){
	echo "bonjour";
	header("Location: formulaire.php"); //si une session est déjà ouverte, renvoi directement vers les  chatroom
	//sinon, reste sur la page de connection
}

if (isset($_GET["goto"])) {
	$action = "dosignin.php?goto=" . $_GET["goto"];
} else {
	$action = "docsignin.php";
}

?>
<!DOCTYPE html>
<html lang="fr">

<head>
	<meta charset="utf-8">
	<title>Pokechat</title>
    <meta name="author" content="Duee-Moreau et Pelletier">
	<!--<link rel="stylesheet" href="../css/tp3.css">
	<link rel="stylesheet" type="text/css" href="style.css">-->
</head>

<body>
	
	<hr>

	<h2>Authentification</h2>
	<form action="<?php echo $action; ?>" method="post">
		Votre login
		<br>
		<input type="text" name="login">
		<br><br>
		votre mot de passe
		<br>
		<input type="password" name="password">
		<br><br>
		<input type="submit" value="Se connecter">
		<input type="reset" value="Annuler">
		<a href="signup.php" style="float:inline-end">Nouvel Utilisateur</a>
	</form>
	<?php
	if (isset($_GET["badlogin"]))
		echo "<h2>Mauvais login/mot de passe </h2>";
	?>
</body>

</html>
