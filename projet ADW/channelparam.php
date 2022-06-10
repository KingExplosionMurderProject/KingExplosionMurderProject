<?php
	session_start();

	function add_new_user($f,$nom,$new_user){              //https://www.delftstack.com/fr/howto/javascript/javascript-json-array-of-objects/#ajouter-un-objet-au-tableau-dobjets-json
	        $handle=fopen($f,"r");
	        $s=fread($handle,filesize($f));                 // -> string
	        $a=json_decode($s,true);                             // -> array
	        //print_r(json_encode($a));
	        echo gettype($a[$nom]["autorisations"]);
	        array_push($a[$nom]["autorisations"],$new_user);
	        print_r(json_encode($a));
	        file_put_contents($f,json_encode($a));
	    }
?>