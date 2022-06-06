<?php
    $mess = file("fichiersCSV/chat2.csv");
    $num = count($mess);
    $affiche = ""; //string avec les messages qui vont être affichés      
    for ($j=0;$j<$num;$j++){
        $affiche .= "<p>".$mess[$j]."</p>";
    }

    echo $affiche;
?>
