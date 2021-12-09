App = {
  web3Provider: null,
  contracts: {}
};

order_queue = {}

async function init () {
  console.log("loading the current data")

  return await initWeb3();
}

async function initWeb3() {
    
  // Modern dapp browsers...
  if (window.ethereum) {
    App.web3Provider = window.ethereum;
    try {
      // Request account access
      await window.ethereum.request({ method: "eth_requestAccounts" });;
    } catch (error) {
      // User denied account access...
      console.error("User denied account access")
    }
  }
  // Legacy dapp browsers...
  else if (window.web3) {
    App.web3Provider = window.web3.currentProvider;
    console.log("detected already injected web3")
  }
  // If no injected web3 instance is detected, fall back to Ganache
  else {
    App.web3Provider = new Web3.providers.HttpProvider('http://localhost:7545');
    console.log("falling back to dedicated network")
  }

  App.web3 = new Web3(App.web3Provider);
  return initContract();
}

function initContract() {

  $.getJSON('Newspaper.json', function(data) {
    // Get the necessary contract artifact file and instantiate it with @truffle/contract
    let  NewspaperArtifact = data;
    App.contracts.Newspaper = TruffleContract(NewspaperArtifact);
  
    // Set the provider for our contract
    App.contracts.Newspaper.setProvider(App.web3Provider);
  
    // Use our contract to retrieve and mark the adopted pets
    console.log("done initalising the contract")
  });
}


function sendOrder() {
  let name = document.getElementById("title").value
  let description = document.getElementById("description").value

  let newspaperInstance;

  App.web3.eth.getAccounts(function(error, accounts) {
    if (error) {
      console.log(error);
    }

    let account = accounts[0];

    App.contracts.Newspaper.deployed().then(function(instance) {
      newspaperInstance = instance;

      // Execute adopt as a transaction by sending account
      return newspaperInstance.SendOrder(name, description.length, {from: account});
      }).then(function(result) {

        // return App.markAdopted();
        console.log("success :)")

        //register this order
        order_queue[account] = {
          "order_text": description,
          "order_nr": null,
          "price": null
        }


        showPrice(account, result.logs)
      }).catch(function(err) {
        console.log(err.message);
      });
  });
}

function showPrice(buyer_account, logs) {
  correct_log = null;
  for(let i = 0; i<logs.length; i++) {
    if(logs[i].event == "PriceSent") {
      correct_log = logs[i];
      break;
    }
  }

  if(correct_log == null) return;

  if(buyer_account != correct_log.args.buyer) {
    console.log("account addressed don't match");
    return;
  }

  //confirm the order
  order_queue[correct_log.args.buyer].order_nr = correct_log.args.order_nr.toNumber();
  order_queue[correct_log.args.buyer].price = correct_log.args.price.toNumber();

  //get the UI elements
  let price_tag = document.getElementById("price_tag");
  let post_button = document.getElementById("post_button");

  //set the visibility
  price_tag.style.visibility = "visible";
  post_button.style.visibility = "visible";
  price_tag.innerHTML = "Price: " + order_queue[correct_log.args.buyer].price + " wei"
}

function post_it() {

  App.web3.eth.getAccounts(function(error, accounts) {
    if (error) {
      console.log(error);
    }

    let account = accounts[0];
    let order_nr = order_queue[account].order_nr;
    let text = order_queue[account].order_text;

    App.contracts.Newspaper.deployed().then(function(instance) {
      newspaperInstance = instance;

      return newspaperInstance.SendPayment(order_nr, text, {from: account, value: order_queue[correct_log.args.buyer].price});
      }).then(function(result) {

        console.log("success on posting")
        addArticle(result.logs);
        hidePrice();
      }).catch(function(err) {
        console.log(err.message);
      });
  });

}

async function addArticle(logs) {
  correct_log = null;
  for(let i = 0; i<logs.length; i++) {
    if(logs[i].event == "ArticlePublished") {
      correct_log = logs[i];
      break;
    }
  }

  if(correct_log == null) return;


  //make an instance
  let instance = await App.contracts.Newspaper.deployed();

  let author_result = await instance.QueryAuthor(correct_log.args.buyer);
  let article_result = await instance.QueryArticle(correct_log.args.article_nr.toNumber());

  console.log(article_result);
  let author_name = App.web3.toAscii(author_result[1]);
  let article_text = article_result[1];


  let clone = document.getElementById("single_container_template").content.cloneNode(true);
  clone.getElementById("author_name").innerHTML = author_name;
  clone.getElementById("article_text").innerHTML = article_text;

  document.getElementById("page_container").appendChild(clone);

}

function hidePrice() {
  //get the UI elements
  let price_tag = document.getElementById("price_tag");
  let post_button = document.getElementById("post_button");

  //set the visibility
  price_tag.style.visibility = "hidden";
  post_button.style.visibility = "hidden";
}


$(function() {
  $(window).load(function() {
    init();
  });
});
