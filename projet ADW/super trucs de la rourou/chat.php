<?php

	// session start permet de récupérer certaines info 
    function printChat($fichier){
        //permet d'afficher les 8 derniers messages de la chatroom
        $mess = file($fichier);

        $num = count($mess);

        $affiche = "<p>"; //string avec les messages qui vont être affichés

        //on veut afficher au maximum 8 messages à la fois

        if ($num<=8){
            foreach($mess as $message){
                $affiche .= "<br>".$message."<br>";
            }
        }
        else {
            for ($j=$num-8;$j<$num;$j++){
                $affiche .= "<br>".$mess[$j]."<br>";
            }
        }
        $affiche .= "<p>";
        echo $affiche;




    }

//tout ce qui est en dessous de ça ne marche pas pour le moment qwq

    function newMessage($fichier){
        //écrit le nouveau message et actualise le chat
        $message = "\n".$_POST['message'];
        // on met les nouveaux messages ensembles
        $chat = file($fichier);
        array_push($chat,$message);
        
	    
	    file_put_contents($fichier,$chat);

        printChat($fichier);
    
    }

    function ecritMess($fichier){
        // on fait une fonction comme ça on l'apelle suivant le salon ouvert
        $input = "<form id='newmess' method='post'>";
        $input .= "<br>".'<input type="text" name="message" id="message">'."<br>";
        $input .= "<br>".'<input type="submit" value="envoyer">'."<br>";
        $input .= "</form>";
        echo $input;

    }

?>