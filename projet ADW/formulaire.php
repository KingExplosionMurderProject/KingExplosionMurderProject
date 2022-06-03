<?php
	require "chat.php"; //ajouté par arwen

	session_start();
	// si l'utilisateur tente d'accéder à cette page sans être authentifié, alors le script le redirige vers le script de login
	
	if (!isset($_SESSION["login"])) {
		$_SESSION["goto"] = "formulaire.php";
		header("Location: signin.php");
		exit();
	}
	else{$login=$_SESSION["login"];}

	$type="energies\électrique.png";
	

?>
<!DOCTYPE html>
<html>
<head>
	<title>Pokechat</title>
    <meta name="author" content="Duee-Moreau et Pelletier">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-0evHe/X+R7YkIZDRvuzKMRqM+OrBnVFBL6DOitfPri4tjfHxaWutUpFmBp4vmVor" crossorigin="anonymous">
	<link rel="stylesheet" type="text/css" href="feuille_css.css" />
	<script src="formulaire.js"></script>
	
	<meta name="viewport" content="width=device-width, initial-scale=1">

</head>
<body>

	<header>										<!-- ENTETE -->
		<img src="images/pokeball.png"/>
        <h1>POKECHAT</h1>
        <img src="images/pokeball.png"/>
    </header>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/js/bootstrap.bundle.min.js" integrity="sha384-pprn3073KE6tl6bjs2QrFaJGz5/SUsLqktiwsUTF55Jfv3qYSDhgCecCxMW52nD2" crossorigin="anonymous"></script>

    <div id="main"> <!-- gros contenaire-->


		<aside class="list">						<!--les autres noms de salons-->

			<div class="boite_user">						<!-- Boite utilisateur -->
				Utilisateur : <strong> <?php echo $login; ?> </strong>
				<br>
				<img src="<?php echo $type;?>" id="boite_user"/>
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

				<div id="spinner">Spinner</div>
				<ul id="list_canaux"></ul>


				<!-- Modal -->
				<div class="modal fade" id="parametresModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
				  <div class="modal-dialog">
				    <div class="modal-content">
				      <div class="modal-header">
				        <h5 class="modal-title" id="exampleModalLabel">Modal title</h5>
				        <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
				      </div>
				      <div class="modal-body">
				        ...
				      </div>
				      <div class="modal-footer">
				        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
				        <button type="button" id="quitterChannel" class="btn btn-primary" data-bs-dismiss="modal">Quitter channel</button>
				      </div>
				    </div>
				  </div>
				</div>


			</form>
		</aside> 



		<div id="chat"> <!--discussion principale-->
			<div id="place">
				<span id="name_chanel">blablabla</span>
				<div id="write">


				<!--ajouté par arwen-->
					<p class="chat">
						<!-- <div class="boite_parametre" style="display:none;">			ajouté par ilane 	
							<?php /*
							echo "<h2>Paramètre du chat "."</h2>"; //savoir quel molette c'est de quel channel
							echo "<h6>créé par </h6>"; //récuperer le créateur du channel
							echo "<input type='button' id='Inviter channel' value='Inviter'>";
							echo "<input type='button' id='Quitter channel' value='Quitter channel'>";*/
							?>
						</div> -->
						<div class="discu">

						<?php 
						
							if (isset($_POST['message']) && $_POST['message'] !== ""){
								newMessage("fichiersCSV\chat2.csv");
							} 
							else {
								printChat("fichiersCSV\chat2.csv");
							}
							
						?>
						</div>

					</p>


			<?php
			//partie écriture des messages
			// une balise <p> par message
			// overflow-y: auto;

				ecritMess("fichiersCSV\chat2.csv"); //boite pour écire les messages

			?>
				<!--fin de l'ajouté par arwen-->

				</div>
			</div>
		</div>
	</div>

</body>
</html>

<!--justify-content: alignement horizontalement, placement -->
