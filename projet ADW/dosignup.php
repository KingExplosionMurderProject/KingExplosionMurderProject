<?php
session_start();
// Ce script vérifie les paramètres envoyés par l'utilisateur
// et, si ces paramètres sont corrects, réalise le signup puis
// redirige l'utilisateur vers le script "signin.php",
// sinon, redirige directement l'utilisateur vers le script
// "signin.php" avec le bon message d'erreur en paramètre
    $users = file("fichiersCSV/users.csv",FILE_IGNORE_NEW_LINES);
    $login = $_POST[ "login" ];
    $mdp1 = $_POST[ "password1" ];
    $mdp2 = $_POST[ "password2" ];
    $type = $_POST["type"];
    
    if ( ! preg_match("/^[a-zA-Z]+$/", $login) ){   //si il y a un élément qui n'est pas une lettre, renvoie une erreur
        header("Location: signup.php?badsignup=1");
        die(); 
    }
    
    $found = false;
    
    foreach ( $users as $line ){         //on va regarder chaque utilisateur déjà inscript
        $a = explode(",",$line);
        if ( $login == $a[0] ){
            header('Location: signup.php?badsignup=2');     //si l'utilisateur existe déja, renvoie un message d'erreur
            exit();
        }
    }

    if ( strlen( $mdp1 ) < 4 ){     // si le mot de passe est trop court, renvoie un message d'erreur
        header("Location: signup.php?badsignup=3");
        exit();
    }
    
    if ( $mdp1 != $mdp2 ){          // si le mot de passe et sa confirmation sont différents, renvoie une erreur
        header("Location: signup.php?badsignup=4");
        exit();
    }

    
    function save_array($f,$l,$mdp,$t){  //sauvegarder le nouveau fichier
        $csv = "";
        foreach ($f as $line) { 
            $tokens = explode(',', $line);
            $csv .= $tokens[0] . ","  . $tokens[1] . "," . $tokens[2] . "\n";
        }
        $csv .= $l . ","  . md5($mdp) . "," . $t . "\n";
        file_put_contents("fichiersCSV/users.csv", $csv);
        /*save_perm($l,"Kanto");*/
    }



    /*save_perm($canaux,$login,$canal);*/
    function save_perm($f,$l,$c){      
        $csv = "";
        foreach ($f as $line) { 
            $tokens = explode(',', $line);
            //echo($c);
            if($tokens[0]==$c){
                echo("in if");
                echo(gettype($tokens[2]));
                array_push($tokens[2],$l);
            }
            $csv .= $tokens[0] . ","  . $tokens[1] . "," . $tokens[2] . "\n";
        }
        file_put_contents("fichiersCSV/canaux.csv", $csv);
    }


    save_array($users,$login,$mdp1,$type);

    $canaux = file("fichiersCSV/canaux.csv",FILE_IGNORE_NEW_LINES);

    save_perm($canaux,$login,"Centre pokemon");


    /*
    if (isset($_SESSION["goto"])) {header('Location: ' . $_SESSION["goto"]);}
    else {header('Location: formulaire.php');}
    exit();
    */




    /*$users[] = "$login," . md5($mdp1).","."$type,"; // on créé l'utilisateur avec ses info pour le fichier
    $newcontent = join("\n", $users) . "\n";
    file_put_contents("users.csv", $newcontent); // on met le nouvel utilisateur dans le fichier
    header("Location: signin.php");*/

// rajouter dans le canaux.csv l'utilisateur (listes où il peut aller)
