window.onload = function () {

	// Recuperer liste des canaux
	
	console.log("hello world");


	function nomChannel(){
		let leNomDuChannel = document.getElementById("leNomDuChannel");
		let valider = document.getElementById("valider");
		leNomDuChannel.style.visibility = "visible";
		valider.style.visibility = "visible";
	}
	let button = document.getElementById("Nouveau channel");
	button.onclick = nomChannel;


};
