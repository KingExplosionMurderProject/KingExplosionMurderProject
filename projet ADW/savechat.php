<?php
include 'chat.php';

    $list = json_decode($_POST['chat']);
    $content = array();

    foreach ($list as $mess){
        $content[] = $mess;
    }
    file_put_contents("fichiersCSV\chat2.csv",$content);   
    $mess = file("fichiersCSV\chat2.csv");
    $num = count($mess);
    $affiche = ""; //string avec les messages qui vont être affichés      
    for ($j=0;$j<$num;$j++){
        $affiche .= "<p>".$mess[$j]."</p>";
    }

    echo $affiche;

?>
