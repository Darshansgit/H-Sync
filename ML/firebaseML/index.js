// ({CustomModelDownloadConditions conditions = new CustomModelDownloadConditions.Builder()
//     .requireWifi()
//     .build();
// FirebaseModelDownloader.getInstance()
//     .getModel("model1", DownloadType.LOCAL_MODEL, conditions)
//     .addOnSuccessListener(new OnSuccessListener<CustomModel>() {
//       @Override
//       public void onSuccess(CustomModel model) {
//         // Download complete. Depending on your app, you could enable
//         // the ML feature, or switch from the local model to the remote
//         // model, etc.
//       }
//     });

const firebaseConfig = {

    apiKey: "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M",
    
    authDomain: "esp2fb-ff2ff.firebaseapp.com",
    
    databaseURL: "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app",
    
    projectId: "esp2fb-ff2ff",
    
    storageBucket: "esp2fb-ff2ff.appspot.com",
    
    messagingSenderId: "70696485797",
    
    appId: "1:70696485797:web:63486f6028ea8822b69e4c"
    
    };

    let input_data = [80,120,85];

// create a function
function predict(input_data) {
    // load the model
    tf.lite('model.tflite').then(model => {
        // make predictions
        model.predict(input_data).print();
    });

    output = model.predict(input_data).print();
    return output;
}


