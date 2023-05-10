//Config data for the database
const firebaseConfig = {

  apiKey: "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M",

  authDomain: "esp2fb-ff2ff.firebaseapp.com",

  databaseURL: "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app",

  projectId: "esp2fb-ff2ff",

  storageBucket: "esp2fb-ff2ff.appspot.com",

  messagingSenderId: "70696485797",

  appId: "1:70696485797:web:63486f6028ea8822b69e4c"

};
//initializing firebase, note the vesion of firebase used because not all the versions of firbase gets initialized
firebase.initializeApp(firebaseConfig);

//just initializing the var
var slno =0;

//defining the reference for the node we are trying to access in the db
var firebaseRef = firebase.database().ref("Users/User1/");

//This function is called to fetch data from FB, also called when there is a change in the db real time beacuse it uses the on() function
function fetchDataFb(){
    //When change in db, call this function       
    firebaseRef.on("value", (snapshot) => {
        //define a array
        var data= []
        //put all the data from snapshots into an array
        snapshot.forEach(function(childSnapshot) {
            data.push(childSnapshot.val());
        });
        //pass each new input array into this func
        addAllItemToTable(data);
    });
}

//This function recieves the data from the above array and it recieves, timestamp, sys, dia and hr in that order
function addAllItemToTable(dataIn){
    //this is where we reset the current table and send new data to it every time there is a change
    slno = 0;
    tbody.innerHTML = "";

    
    //Now for each array update, push the values into a new function, dont need this but shows where data is refreshed
    dataIn.forEach(element => {
        // slno++;
        
        AiFunc(element.timestamp, element.Systolic,element.Diastolic, element.HearRate);
        // addItemToTable(slno, element.timestamp,element.Systolic,element.Diastolic,element.HearRate);
        
    });
}

//this is the main fucntion
function AiFunc(timestamp,sys, dia, hr){
    //cure the incomeing data to feed into the ai model
    const myArray = [hr, sys, dia]; // convert the variables to an array
    newFunc(myArray); // call newFunc with the array

    //load the model
    async function loadModel(){
        return tf.loadLayersModel('/3valModel/model.json');
    }
    
    //this is where the magic happens
    async function newFunc(inputArr){
        
        const model = await loadModel();
        //if you dont console log the model, it wont work, dont know why, most probably beacuse the output cant catch up with the model as it doesnt load fast enough
        console.log(model);
    
            let result = await model.predict(tf.tensor2d(inputArr, [1, 3])).dataSync();
    
            let output = tf.argMax(result).dataSync();
            output = Number(output)+1;

            //this is where we shape the data into the form in which we expect it on the table and send it
           
            
            renderTable(timeconv(timestamp), sys, dia, hr, diag(output));
          
}}

//calling the table body
var tbody = document.getElementById('tbody1');

//table gets rendered here
function renderTable(timestamp, sys, dia, hr, diagnosis)
{
    //declare a row element, add cells to the row using append child method and decide what gets appended where
    let trow = document.createElement("tr");
    let td1 = document.createElement('td');
    let td2 = document.createElement('td');
    let td3 = document.createElement('td');
    let td4= document.createElement('td');
    let td5 = document.createElement('td');
    let td6 = document.createElement('td');

    td1.innerHTML = ++slno;
    td2.innerHTML = timestamp;
    td3.innerHTML = sys;
    td4.innerHTML = dia;
    td5.innerHTML = hr;
    td6.innerHTML = diagnosis;

    trow.appendChild(td1);
    trow.appendChild(td2);
    trow.appendChild(td3);
    trow.appendChild(td4);
    trow.appendChild(td5);
    trow.appendChild(td6);

    tbody.appendChild(trow);
}

//converts timestamp from epoch time to YY-MM-DD format 
function timeconv(timestamp)
{
    var date = new Date(timestamp*1000); 
    var resultFormat = date.toISOString().split('T')[0]
    return resultFormat;
}

function diag(diag)
{
    if (diag==1)
    {
        return "Hypotension";
    }
    else if (diag ==2)
    {
        return "Normal"
    }
    else if (diag ==3)
    {
        return "Hypertension"
    }

}
//calling the main function everytime the script tag loads.
fetchDataFb();