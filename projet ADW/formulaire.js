window.onload = function () {

	// Recuperer liste des canaux
	
	console.log("hello world");


	function nomChannel(){
		let leNomDuChannel = document.getElementById("leNomDuChannel");
		let valider = document.getElementById("valider");
		leNomDuChannel.style.visibility = "visible";
		valider.style.visibility = "visible";
	}

	function changerChannel(){

		let nc = document.getElementById("name_chanel");
		nc.innerHTML = "Nous sommes à "+this.innerHTML; //this = channel[i]
	}


	let button = document.getElementById("Nouveau channel");
	button.onclick = nomChannel;

	var channel = document.querySelectorAll(".nomRegion");
	for(i=0;i<channel.length;i++){
		channel[i].onclick= changerChannel; 
	}


};
