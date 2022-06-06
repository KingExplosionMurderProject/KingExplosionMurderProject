<?php
	require "chat.php";
	session_start();
	// si l'utilisateur tente d'accéder à cette page sans être authentifié, alors le script le redirige vers le script de login
	
	if (!isset($_SESSION["login"])) {
		$_SESSION["goto"] = "formulaire.php";
		header("Location: signin.php");
		exit();
	}
	$login = $_SESSION["login"];



?>
<!DOCTYPE>
<html>
<head>
	<title>Pokechat</title>
    <meta name="author" content="Duee-Moreau et Pelletier">
	<link rel="stylesheet" type="text/css" href="feuille_css.css" />


	<!-- <script type="text/javascript" src="js/simpleajax.js"></script> 
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />-->
	<script src="formulaire.js"></script>
</head>
<body>

	<header>
		<img src="images/pokeball.png"/>
        <h1>POKECHAT</h1>
        <img src="images/pokeball.png"/>
    </header>

    <!--
    <div id="top">
		Utilisateur : <strong><?php //echo $login; ?></strong> - <a href="signout.php">déconnexion</a>
	</div>
	-->

    <div id="main"> <!-- gros contenaire-->
		<div class="list"><!--les autres noms de salons-->
			<div class="boite_user">
				Utilisateur : <strong> <?php echo $login; ?> </strong>
				<br>
				<a href="signout.php">déconnexion</a>
			</div>
				<h2>Blabla 1</h2>
				blablabla
				<br>
		</div> 
		<div class="chat"> <!--discussion principale-->
			<h2>Blabla 2</h2>
		<!-- mettre une balise ici pour afficher le chat après chaque submit -->
		<p class="chat">

			<?php 
			
				if (isset($_POST['message']) && $_POST['message'] !== ""){
					newMessage("fichiersCSV/chat2.csv");
				} 
				else {
					printChat("fichiersCSV/chat2.csv");
				}
				
			?>

		<p>


			<?php
			//partie écriture des messages

				ecritMess("fichiersCSV/chat2.csv"); //boite pour écire les messages

			?>
			
	</div>

</body>
</html>

<!--justify-content: alignement horizontalement, placement -->