function signUp() {
    var email = document.getElementById("email").value;
    var password = document.getElementById("password").value;
  
    firebase.auth().createUserWithEmailAndPassword(email, password)
      .then(function(userCredential) {
        var user = userCredential.user;
        alert("Sign up successful!");
        // Redirect to home page or user profile page
      })
      .catch(function(error) {
        var errorCode = error.code;
        var errorMessage = error.message;
        alert(errorMessage);
      });
  }
  