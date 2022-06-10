<?php
	session_start();

	//ici nous créons un nouveau channel
	//il sera ajouter au csv

	$channel = "fichiersCSV\\canaux.json";
	if(isset($_POST["leNomDuChannel"])){
		$nomChannel = $_POST["leNomDuChannel"];
	} else {
		//pb car il n'a pas mis le nom
		$nomChannel ="you re a loser";
	}
	

	/*foreach ( $channel as $line ){         //on va regarder chaque nom de channel déjà inscript
        $a = explode(",",$line);
        if ( $nomChannel == $a[0] ){
            //header('Location: signup.php?badsignup=2');     //si l'utilisateur existe déja, renvoie un message d'erreur
            echo "pb";
            exit();
        }
    }*/

    function save_array($f,$nom,$crea, $auto){
        $handle=fopen($f,"r");
        $s=fread($handle,filesize($f));                 // -> string
        $a=json_decode($s);                             // -> array
        $a->$nom=array("createur" => $crea , "autorisations" => $auto);
        print_r(json_encode($a));
        file_put_contents($f,json_encode($a));
    }


    save_array($channel,$nomChannel,"createur",[]);
    $_SESSION["login"] = $login;
    header('Location: formulaire.php');
?>