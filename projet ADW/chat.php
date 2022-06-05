<?php

//le dernier message envoyé est automatiquement gardé, ce qui pose problème

    function printChat($fichier){
        //appelé une seule fois, lors de la première connection
        //avavnt l'envoie des messages
        //permet d'afficher les 8 derniers messages de la chatroom
        $mess = file($fichier);
        $num = count($mess);
        $affiche = ""; //string avec les messages qui vont être affichés      
        for ($j=0;$j<$num;$j++){
            $affiche .= "<p>".$mess[$j]."</p>";
        }

        echo $affiche;

    }

    function ecritMess(){
        // on fait une fonction comme ça on l'apelle suivant le salon ouvert
        //changer pour du textarea
        $input = "<br>".'<textarea name="message" id="message" autocomplete="off" placeholder="Discutez avec vos amis">'.'</textarea>'."<br>";
        $input .= "<br>".' <input type="submit" id="envoyer" value="envoyer">'."<br>";
        echo $input;

    }

?>
