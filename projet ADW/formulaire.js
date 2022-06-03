window.onload = function () {

	//import readTextFile() from utils.js;
	// Recuperer liste des canaux
	//https://developer.mozilla.org/fr/docs/Web/JavaScript/Guide/Modules
	
	console.log("hello world");

	var canaux = null;
	var currentChannel = null;

	var login = document.getElementById("login").innerHTML;
	var users = null;
	var currentUsers = null;
	
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
			canaux = res.split("\n");
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


		readTextFile('fichiersCSV/users.csv').then((res) => {
			// Success
			users = res.split("\r\n");
			users = users.filter((line) => {
				// For each, execution pour chaque line
				return (line && line.length > 0);
			});
			users = users.map((col) => {
				return col.split(',');
			});
			// liste de users recupere
			//console.log(users);
		}, (err) => {
			// Error
			console.log(err);
			// Afficher un message d'erreur
			users = [];
		}).finally(() => {
			let i=0;
			users.forEach((user)=> {
				if(user[0]==login){
					whichType(user);
				}
				i++;
			});
			
			//refreshChannels();
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
			/*regionDiv.setAttribute("nomRegion");*/
			// Creer un deuxieme <div> pour le nom de la region
			let nomRegionDiv = document.createElement('div');
			nomRegionDiv.classList.add('nomRegion');
			nomRegionDiv.innerHTML = canal[0];
			// Creer molette de parametres
			let moletteDiv = document.createElement('div');
			moletteDiv.classList = 'parametre d-flex justify-content-center align-items-center';
			moletteDiv.innerHTML = "<img class='molette' src='images/molette.png'>"
			// Evenement quand on clisque sur la div
			regionDiv.addEventListener('click', event => {
				changerChannel(canal);
			});
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

	function whichType(user){
		//let img = document.getElementById("energiepp");
		document.getElementById("energiepp").src = "energies\\" + user[2] +".png";
	}


	function changerChannel(canal){
		console.log(canal);
		let nc = document.getElementById("name_chanel");
		nc.innerHTML = "Nous sommes à "+canal[0]; //this = channel[i]
		let cc = document.getElementById("currentChannel");
		cc.innerHTML = canal[0];
	}

	function param(canal){
		// Mettre à jour le titre de la modal
		let modalTitle = document.getElementById("modalTitle");
		modalTitle.innerHTML = 'Paramètre du chat ' + canal[0];
		let modalText = document.getElementById("modal-body");
		modalText.innerHTML = "créé par l'utilisateur "+ canal[1];

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
