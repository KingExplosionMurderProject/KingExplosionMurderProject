<?php
/*_________________________________________________________Destruction de la session_________________________________________________________*/

    // dans cette partie, on détruit la session
    // et on redirige l'utilisateur vers la page de login
    session_start();
    session_unset();
    session_destroy();
    header("Location: signin.php");
?>
