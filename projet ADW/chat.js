// une fois le bouton submit appuyé, on récupère le message et le nom d'utilisateur
// ensuite on récupère les anciens messages
// et on change le html du chat

window.onload = function () {


//let chat = document.querySelector(".discu");
    let sub = document.getElementById("envoyer");
    sub.addEventListener('click', event => {
        message();})


    // on récupère le message écrit
    function message(){
        let channel = document.getElementById('currentChannel').value;
        console.log(channel);
        //on récupère la chanel dans laquel on est
        let message = document.getElementById('message').value;
        console.log(message);
        //on récupère ce qui a été écrit
        message.innerHTML = "";
        
    }


}
