window.onload = function () {
	//quand on clique il vérifie si on est déja connecter sinon il propose de se loguer.

	var miniature = document.querySelectorAll(".miniature");
	for(let i = 0; i < 3; i++){
		miniature[i].onclick= go_chat; 
	}

	function go_chat(){
		window.location.href = "formulaire.php";
		console.log("go chatter");
	}

};
