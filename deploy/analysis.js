const firebaseConfig = {

    apiKey: "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M",
  
    authDomain: "esp2fb-ff2ff.firebaseapp.com",
  
    databaseURL: "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app",
  
    projectId: "esp2fb-ff2ff",
  
    storageBucket: "esp2fb-ff2ff.appspot.com",
  
    messagingSenderId: "70696485797",
  
    appId: "1:70696485797:web:63486f6028ea8822b69e4c"
  
  };
firebase.initializeApp(firebaseConfig);

var database = firebase.database();

async function loadModel()
{
   
   
}


fetchFB();


function fetchFB()
{
    
    database.ref("Users/bpData").on("value", function (snapshot) {
        var data = snapshot.val();
        // console.log(data);
        let values = Object.values(data);
        // console.log(values.length);
    })
}

function renderTable()
{
// create a table
 
}
