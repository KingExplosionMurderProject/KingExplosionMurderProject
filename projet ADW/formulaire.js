window.onload = function() {
	// Remarque à faire :
    // import readTextFile() from utils.js;
    // Recuperer liste des canaux
    // https://developer.mozilla.org/fr/docs/Web/JavaScript/Guide/Modules

    // setTimeout(() => {		Si on veut mieux voir le spinner pour mettre un feu rouge au code
    // }, 3000);

    // Initialisation des variables :
    var canaux = null;
    var canauxObj = null;
    var currentChannel = null;
    /*var last_list_canaux = [];*/

    var login = document.getElementById("login").innerHTML;
    var users = null;
    var currentUser = null;


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
            request.onreadystatechange = function() {
                if (request.readyState === 4) {
                    if (request.status === 200 || request.status == 0) {
                        var allText = request.responseText;
                        // Success
                        resolve(allText);
                    } else {
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
    readTextFile('fichiersCSV/canaux.json').then((res) => {
    	canauxObj = JSON.parse(res);
    	console.log(canauxObj["Kanto"]["autorisations"]);
    	canaux = [];
    	for (const nom in canauxObj)
    		canaux.push(nom);
    	autocomplete(document.getElementById("RuC"), canaux);
        // Success
        // liste de canaux recupere
        //console.log(canaux);
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

        users = res.split("\n");
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
        let i = 0;
        users.forEach((user) => {
        	//console.log(user);
            if (user[0] == login) {
                whichType(user);
            }
            i++;
        });
        refreshChannels();
    });

    function isInChannel(c){
    	let tab = canauxObj[c]["autorisations"] ;
    	console.log(c);
    	for (var i in tab) {
    		/*console.log(login);
    		console.log(i);*/
   			if(login==tab[i]){
				return true;
			}
		}
    	return false;
    	//return true;
    }



    function refreshChannels() {
        let ul = document.getElementById("list_canaux");
        // On vide le ul pour prepare le prochain affichage
        ul.innerHTML = "";
        canaux.forEach((canal) => {
        	//console.log(canal);
            // Create une balise <li>
            if(isInChannel(canal)){
	            let li = document.createElement('li');
	            // Creer un premier <div> pour la region
	            let regionDiv = document.createElement('div');
	            regionDiv.classList = 'region d-flex justify-content-center align-items-center';
	            /*regionDiv.setAttribute("nomRegion");*/
	            // Creer un deuxieme <div> pour le nom de la region
	            let nomRegionDiv = document.createElement('div');
	            nomRegionDiv.classList.add('nomRegion');
	            nomRegionDiv.innerHTML = canal;
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
	        }
        });
    }


    function nomChannel() {
        let leNomDuChannel = document.getElementById("leNomDuChannel");
        let valider = document.getElementById("valider");
        leNomDuChannel.style.visibility = "visible";
        valider.style.visibility = "visible";
    }

    function whichType(user) {					//	Connaitre le type de l'utilisateur courant
        //console.log(user[2]);
        document.getElementById("energiepp").src = "energies\\" + user[2] + ".png";
    }


    function changerChannel(canal) {
        let nc = document.getElementById("name_chanel");
        nc.innerHTML = "Nous sommes à " + canal[0]; //this = channel[i]
        let cc = document.getElementById("currentChannel");
        cc.innerHTML = canal[0];
    }

    function param(canal) {
        // Mettre à jour le titre de la modal
        let modalTitle = document.getElementById("modalTitle");
        modalTitle.innerHTML = 'Paramètre du chat ' + canal;
        //console.log(canauxObj);
        let modalText = document.getElementById("modal-body");
        modalText.innerHTML = "Créé par l'utilisateur <strong>" + canauxObj[canal]["createur"] + "</strong>.<br>";
         modalText.innerHTML += "Les utilisateurs autorisés a accéder au canal sont : " + canauxObj[canal]["autorisations"] + ".";
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
    for (i = 0; i < channel.length; i++) {
        channel[i].onclick = changerChannel;
    }

    let buttonP = document.getElementsByClassName("molette");
    for (i = 0; i < buttonP.length; i++) {
        buttonP[i].onclick = param;
    }

    document.getElementById("quitterChannel").addEventListener('click', function() {
        console.log('quitter');
        //console.log(currentChannel);
        // Executer le code pour supprimer l'utilisateur du canal
    });





    //recherche chat------------------------------------------------------------------------------------------------------

    function autocomplete(inp, arr) {
        /*the autocomplete function takes two arguments,
        the text field element and an array of possible autocompleted values:*/
        var currentFocus;
        //console.log(inp);
        //console.log(arr);
        /*execute a function when someone writes in the text field:*/
        inp.addEventListener("input", function(e) {
            var a, b, i, val = this.value;
            /*close any already open lists of autocompleted values*/
            closeAllLists();
            if (!val) { return false; }
            currentFocus = -1;
            /*create a DIV element that will contain the items (values):*/
            a = document.createElement("DIV");
            a.setAttribute("id", this.id + "autocomplete-list");
            a.setAttribute("class", "autocomplete-items");
            /*append the DIV element as a child of the autocomplete container:*/
            this.parentNode.appendChild(a);
            /*for each item in the array...*/
            for (i = 0; i < arr.length; i++) {
                /*check if the item starts with the same letters as the text field value:*/
                //console.log(arr[i], val);
                if (arr[i].toLowerCase().indexOf(val.toLowerCase()) != -1) {
                // if (arr[i].substr(0, val.length).toUpperCase() == val.toUpperCase()) {
                    /*create a DIV element for each matching element:*/
                    b = document.createElement("DIV");
                    /*make the matching letters bold:*/
                    // b.innerHTML = "<strong>" + arr[i].substr(0, val.length) + "</strong>";
                    // b.innerHTML += arr[i].substr(val.length);
                    b.innerHTML = arr[i];
                    /*insert a input field that will hold the current array item's value:*/
                    b.innerHTML += "<input type='hidden' value='" + arr[i] + "'>";
                    /*execute a function when someone clicks on the item value (DIV element):*/
                    b.addEventListener("click", function(e) {
                        /*insert the value for the autocomplete text field:*/
                        inp.value = this.getElementsByTagName("input")[0].value;
                        /*close the list of autocompleted values,
                        (or any other open lists of autocompleted values:*/
                        closeAllLists();
                    });
                    a.appendChild(b);
                }
            }
        });
        /*execute a function presses a key on the keyboard:*/
        inp.addEventListener("keydown", function(e) {
            var x = document.getElementById(this.id + "autocomplete-list");
            if (x) x = x.getElementsByTagName("div");
            if (e.keyCode == 40) {
                /*If the arrow DOWN key is pressed,
                increase the currentFocus variable:*/
                currentFocus++;
                /*and and make the current item more visible:*/
                addActive(x);
            } else if (e.keyCode == 38) { //up
                /*If the arrow UP key is pressed,
                decrease the currentFocus variable:*/
                currentFocus--;
                /*and and make the current item more visible:*/
                addActive(x);
            } else if (e.keyCode == 13) {
                /*If the ENTER key is pressed, prevent the form from being submitted,*/
                e.preventDefault();
                if (currentFocus > -1) {
                    /*and simulate a click on the "active" item:*/
                    if (x) x[currentFocus].click();
                }
            }
        });

        function addActive(x) {
            /*a function to classify an item as "active":*/
            if (!x) return false;
            /*start by removing the "active" class on all items:*/
            removeActive(x);
            if (currentFocus >= x.length) currentFocus = 0;
            if (currentFocus < 0) currentFocus = (x.length - 1);
            /*add class "autocomplete-active":*/
            x[currentFocus].classList.add("autocomplete-active");
        }

        function removeActive(x) {
            /*a function to remove the "active" class from all autocomplete items:*/
            for (var i = 0; i < x.length; i++) {
                x[i].classList.remove("autocomplete-active");
            }
        }

        function closeAllLists(elmnt) {
            /*close all autocomplete lists in the document,
            except the one passed as an argument:*/
            var x = document.getElementsByClassName("autocomplete-items");
            for (var i = 0; i < x.length; i++) {
                if (elmnt != x[i] && elmnt != inp) {
                    x[i].parentNode.removeChild(x[i]);
                }
            }
        }
        /*execute a function when someone clicks in the document:*/
        document.addEventListener("click", function(e) {
            closeAllLists(e.target);
        });
    }

    




    // partie du chat-----------------------------------------------------------------------------------------------------
    //setInterval(loadChat, 1000); //et non
    //setInterval(chatLoad, 1000);

    let sub = document.getElementById("envoyer");
    sub.addEventListener('click', event => {
        message();
    })


    function message() {


        //on ajoute le message aux anciens
        add();

        //on sauvegarde tout ça
        saveChat();


        //je sais que c'est pas forcément la meilleur manière ou propre
        function add() {
            //on récupère le nouveau message
            let message = document.getElementById('message').value + "\n";

            //on récupère la boite où sont affiché les messages
            let chatroom = document.getElementById('emplacement');

            //on créé le nouvel élément message et on l'ajoute
            let toAdd = document.createElement("p");
            toAdd.innerHTML = message;
            chatroom.appendChild(toAdd);
            document.getElementById('message').value = "";


        }



    }


    //fonctions pour save le chat

    function saveChat() {
        let array = [];

        //on récupère l'intérieur du chat
        let chat = document.getElementById('emplacement').innerHTML;

        //on enlève les balises <p>
        array = chat.split("<p>");
        let finalChat = [];
        let message;
        let number = array.length;
        for (let i = 1; i < number; i++) {
            message = array[i].split('</p>');
            finalChat.push(message[0]);

        }
        new simpleAjax("savechat.php", "post", "chat=" + JSON.stringify(finalChat), load, fail);




    }

    //fonction pour load le chat
    function loadChat() {
        new simpleAjax("loadchat.php", "post", "", load, fail);
    }


    function load(request) {
        let chat = document.getElementById('emplacement');
        chat.innerHTML = request.responseText;
    }

    function fail() {
        alert("problème");
    }


};