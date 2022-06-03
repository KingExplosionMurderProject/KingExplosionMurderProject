window.onload = function () {

	// import readTextFile from utils.js
	// Recuperer liste des canaux
	//https://developer.mozilla.org/fr/docs/Web/JavaScript/Guide/Modules
	
	console.log("hello world");

	var canaux = null;
	var currentChannel = null;
	// var fetchingCanaux = true;

	// A mettre dans un fichier "utils" qui sera commun avec d'autres fichiers JS
	function readTextFile(file) {
		// Promise pour asynchrone
		return new Promise((resolve, reject) => {
			// Creation d'un objet de type XMLHTTPRequest
			var request = new XMLHttpRequest();
			// true pour asynchrone
		    request.open("GET", file, true);
		    // Pour eviter de regarder le cache non atualisé
		    request.setRequestHeader("Cache-Control", "no-cache, no-store, max-age=0");
		    request.onreadystatechange = function () {
		        if(request.readyState === 4) {
		            if(request.status === 200 || request.status == 0) {
		                var allText = request.responseText;
		                // Success
		                resolve(allText);
		            }
		            else {
		            	// Error
		            	reject('error');
		            }
		        }
		    }
		    request.send(null);
		});
	}

	// Execute le code apres 3 secondes d'attente
	// setTimeout(() => {
	// }, 3000);
		readTextFile('fichiersCSV/canaux.csv').then((res) => {
			// Success
			canaux = res.split("\r\n");
			canaux = canaux.filter((line) => {
				// For each, execution pour chaque line
				return (line && line.length > 0);
			});
			canaux = canaux.map((col) => {
				return col.split(',');
			});
			// liste de canaux recupere
			console.log(canaux);
		}, (err) => {
			// Error
			console.log(err);
			// Afficher un message d'erreur
			canaux = [];
		}).finally(() => {
			// Appellé apres Success ou Error
			// fetchingCanaux = false;
			let spinner = document.getElementById("spinner");
			spinner.classList.add('hidden');
			refreshChannels();
		});
	

	function refreshChannels() {
		let ul = document.getElementById("list_canaux");
		// On vide le ul pour prepare le prochain affichage
		ul.innerHTML = "";
		canaux.forEach((canal) => {
			// Create une balise <li>
			let li = document.createElement('li');
			// Creer un premier <div> pour la region
			let regionDiv = document.createElement('div');
			regionDiv.classList = 'region d-flex justify-content-center align-items-center';
			// Creer un deuxieme <div> pour le nom de la region
			let nomRegionDiv = document.createElement('div');
			nomRegionDiv.classList.add('nomRegion');
			nomRegionDiv.innerHTML = canal[0];
			// Creer molette de parametres
			let moletteDiv = document.createElement('div');
			moletteDiv.classList = 'parametre d-flex justify-content-center align-items-center';
			moletteDiv.innerHTML = "<img class='molette' src='images/molette.png'>"
			// Evenement quand on clique sur la molette
			moletteDiv.addEventListener('click', event => {
				param(canal);
			});
			// Poupees russes
			regionDiv.append(nomRegionDiv);
			regionDiv.append(moletteDiv);
			li.append(regionDiv);
			ul.append(li);
		});
	}


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

	function param(canal){
		// Mettre à jour le titre de la modal
		let modalTitle = document.getElementById("exampleModalLabel");
		modalTitle.innerHTML = 'Paramètre du chat ' + canal[0];
		// Creation de mon objet Modal
		const myModal = new bootstrap.Modal(document.getElementById('parametresModal'));
		// Utilisation de la function show
		// https://getbootstrap.com/docs/5.2/components/modal/#methods
		myModal.show();
		// Save channel
		currentChannel = canal;
		// Quand ma modal se ferme
		const myModalEl = document.getElementById('parametresModal')
		myModalEl.addEventListener('hidden.bs.modal', event => {
			currentChannel = null;
		});



		/*let nameMol = this.parentNode.parentNode;
		let final = document.getElementsByClassName("boite_parametre")[0];
		final.style.display = "block";
		let title = final.querySelector(".boite_parametre > h2");		//1
		title.innerHTML = "Paramètre du chat : "+ nameMol.innerHTML;	//2*/
	}

	let buttonNC = document.getElementById("Nouveau channel");
	buttonNC.onclick = nomChannel;

	var channel = document.querySelectorAll(".nomRegion");
	for(i=0;i<channel.length;i++){
		channel[i].onclick= changerChannel; 
	}

	let buttonP = document.getElementsByClassName("molette");
	for(i=0;i<buttonP.length;i++){
		buttonP[i].onclick= param; 
	}

	document.getElementById("quitterChannel").addEventListener('click', function() {
		console.log('quiter');
		console.log(currentChannel);
		// Executer le code pour supprimer l'utilisateur du canal
	});

};
