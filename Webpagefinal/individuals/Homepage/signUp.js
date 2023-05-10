// Your web app's Firebase configuration
var firebaseConfig = {

  apiKey: "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M",

  authDomain: "esp2fb-ff2ff.firebaseapp.com",

  databaseURL: "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app",

  projectId: "esp2fb-ff2ff",

  storageBucket: "esp2fb-ff2ff.appspot.com",

  messagingSenderId: "70696485797",

  appId: "1:70696485797:web:63486f6028ea8822b69e4c"

  
  };
  
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);
  
  // Initialize variables
  const auth = firebase.auth()
  const database = firebase.database()
  
  // Set up our register function
  function register () {
    // Get all our input fields
    email = document.getElementById('email').value
    password = document.getElementById('password').value
    // full_name = document.getElementById('full_name').value
    
    // Validate input fields
    if (validate_email(email) == false || validate_password(password) == false) {
        alert('Email or Password is invalid, Try again!')
        return
      // Don't continue running the code
    }
    // Move on with Auth
    auth.createUserWithEmailAndPassword(email, password)
    .then(function() {
      // DOne
        alert('User Created!!')
        firebase.auth().onAuthStateChanged(user => {
          if(user) {
            window.location = 'signIn.html'; //After successful login, user will be redirected to home.html
          }
        });

    })
    .catch(function(error) {
      // Firebase will use this to alert of its errors
        var error_code = error.code
        var error_message = error.message
    
        alert(error_message)
    })
  }
  
  // Validate Functions
  function validate_email(email) {
    expression = /^[^@]+@\w+(\.\w+)+\w$/
    if (expression.test(email) == true) {
      // Email is good
      return true
    } else {
      // Email is not good
      return false
    }
  }
  
  function validate_password(password) {
    // Firebase only accepts lengths greater than 6 yu can set up requirements like caps and numbers here, dont care tho rn
    if (password < 6) {
      return false
    } else {
      return true
    }
  }
  
  function validate_field(field) {
    if (field == null) {
      return false
    }
  
    if (field.length <= 0) {
      return false
    } else {
      return true
    }
  }