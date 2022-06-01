<?php
	session_start();
	// si l'utilisateur tente d'accéder à cette page sans être authentifié, alors le script le redirige vers le script de login
	
	if (!isset($_SESSION["login"])) {
		$_SESSION["goto"] = "formulaire.php";
		header("Location: signin.php");
		exit();
	}
	else{$login=$_SESSION["login"];}
	

?>
<!DOCTYPE html>
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


    <div id="main"> <!-- gros contenaire-->
		<div class="list"><!--les autres noms de salons-->
			<div class="boite_user">
				Utilisateur : <strong> <?php echo $login; ?> </strong>
				<br>
				<a href="signout.php">déconnexion</a>
			</div>
			<form action="channelsignup.php" method="post">
				<h2>Canaux</h2>

				<input type="button" id="Nouveau channel" value="Nouveau channel">
				<br>
				<input id="leNomDuChannel" name="leNomDuChannel" type="text" size="10" style="visibility: hidden">
				<input type="submit" id="valider" value="OK" style="visibility: hidden">
				
				<br>
				<br>
				<?php
				foreach(file("fichiersCSV/canaux.csv", FILE_IGNORE_NEW_LINES) as $line){
					$tokens = explode(',',$line);
					echo "<div class='region'>";
					echo $tokens[0];
					echo "</div>";
					echo "<br>";
				}
				?>
			</form>
		</div> 
		<div id="chat"> <!--discussion principale-->
			<div id="place">
				<h2>Blabla 2</h2>
				<span id="name_chanel">blablabla</span>
				<div id="write">
					Tapez votre texte !
				</div>
			</div>
		</div>
	</div>

</body>
</html>

<!--justify-content: alignement horizontalement, placement -->
