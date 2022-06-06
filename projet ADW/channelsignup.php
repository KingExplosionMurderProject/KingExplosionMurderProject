<?php
	session_start();

	//ici nous créons un nouveau channel
	//il sera ajouter au csv

	$channel = file("fichiersCSV/canaux.csv",FILE_IGNORE_NEW_LINES);
	if(isset($_POST["leNomDuChannel"])){
		$nomChannel = $_POST["leNomDuChannel"];
	} else {
		//pb car il n'a pas mis le nom
		$nomChannel ="you re a loser";
	}
	

	foreach ( $channel as $line ){         //on va regarder chaque nom de channel déjà inscript
        $a = explode(",",$line);
        if ( $nomChannel == $a[0] ){
            //header('Location: signup.php?badsignup=2');     //si l'utilisateur existe déja, renvoie un message d'erreur
            echo "pb";
            exit();
        }
    }

	function save_array($f,$nom,$crea,$a){  //sauvegarder le nouveau fichier
        $csv = "";
        foreach ($f as $line) { 
            $tokens = explode(',', $line);
            $csv .= $tokens[0] . ","  . $tokens[1] . "\n";
        }
        $csv .= $nom . ","  . $crea . "," . $a . "\n";
        file_put_contents("fichiersCSV/canaux.csv", $csv);
    }

    save_array($channel,$nomChannel,"créateur","[les autorisations]");
    $_SESSION["login"] = $login;
    header('Location: formulaire.php');
?>
