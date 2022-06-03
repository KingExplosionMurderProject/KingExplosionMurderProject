<?php

//le dernier message envoyé est automatiquement gardé, ce qui pose problème


    // session start permet de récupérer certaines info 
    function printChat($fichier){
        //permet d'afficher les 8 derniers messages de la chatroom
        $mess = file($fichier);

        $num = count($mess);

        $affiche = ""; //string avec les messages qui vont être affichés

        //on veut afficher au maximum 8 messages à la fois

        if ($num<=8){
            foreach($mess as $message){
                $affiche .= "<p>".$message."<p>";
            }
        }
        else {
            for ($j=$num-8;$j<$num;$j++){
                $affiche .= "<p>".$mess[$j]."<p>";
            }
        }
        echo $affiche;




    }


    function newMessage($fichier){
        //écrit le nouveau message et actualise le chat
        $message = "\n".$_POST['message'];
    header("Location: formulaire.php"); //permet que si on actualise la page juste apres avoir envoyé le message, celui*ci n'est pas renvoyé
        // on met les nouveaux messages ensembles
        $chat = file($fichier);
        array_push($chat,$message);
        
        
        file_put_contents($fichier,$chat);

        printChat($fichier);
    
    }

    function ecritMess($fichier){
        // on fait une fonction comme ça on l'apelle suivant le salon ouvert
        $input = "<form id='newmess' method='post'>";
        $input .= "<br>".'<input type="text" name="message" id="message" autocomplete="off" placeholder="Discutez avec vos amis">'."<br>";
        $input .= "<br>".'<input type="submit" value="envoyer" id="submit">'."<br>";
        $input .= "</form>";
        echo $input;

    }

?>
