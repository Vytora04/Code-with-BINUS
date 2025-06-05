const sign_in_btn = document.querySelector("#sign-in-btn");
const sign_up_btn = document.querySelector("#sign-up-btn");
const container = document.querySelector(".container");

sign_up_btn.addEventListener("click", () => {
  container.classList.add("sign-up-mode");
});

sign_in_btn.addEventListener("click", () => {
  container.classList.remove("sign-up-mode");
});

const backButton = document.querySelector(".back-button");

backButton.addEventListener("click", () => {
   window.location.href = '/html/main-page.html';
});

function validateUserLogin(){
    const email = document.getElementById("email");
    const password = document.getElementById("password");

    const emailValue = email.value.trim();
    const passwordValue = password.value.trim();  

    if(!emailValue.endsWith("@gmail.com") && !emailValue.endsWith("@outlook.com")){
      alert("E-mail must end with @gmail.com or @outlook.com");
      return;
    }

    if (passwordValue.length < 8) {
      alert("Password must be at least 8 characters long");
      return;
    }
}

function validateUserRegister(){
    const email = document.getElementById("email");
    const password = document.getElementById("password");
    const gender = document.getElementById("gender");

    const emailValue = email.value.trim();
    const passwordValue = password.value.trim(); 

    if(!emailValue.endsWith("@gmail.com") && !emailValue.endsWith("@outlook.com")){
      alert("E-mail must end with @gmail.com or @outlook.com");
      return;
    }

    if (passwordValue.length < 8) {
      alert("Password must be at least 8 characters long");
      return;
    }

    if(gender.value === "none")
    {
      alert("Select either Male or Female");
      return
    }
}

const loginButton = document.querySelector(".login-button");
loginButton.addEventListener("click", () => {
  window.location.href = '/html/song-page-logged.html';
});