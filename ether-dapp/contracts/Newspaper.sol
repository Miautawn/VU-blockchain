// SPDX-License-Identifier: MIT
pragma solidity >=0.4.22 <0.9.0;

contract Newspaper {

    address payable newsletter;

    //this should be dynamic, but it's static for demonstation purposes
    address payable redactor = payable(0xc11eceEbA1BF3868C21A52E2053f333D082da378);

    uint order_seqence = 0;
    uint article_sequence = 0;

    struct Author {
        address author_address;
        bytes32 author_name;
    }

    struct Order {
        address author_address;
        uint text_length;
        uint price;
    }

    struct Article {
        address article_author_address;
        string article_text;
        uint order_number;
    }

    // author dictionary
    mapping (address => Author) authors;

    // order dictionary
    mapping (uint => Order) orders;

    // article dictionary
    mapping (uint => Article) articles;

    // Event triggered when the person sends a posting request
    event OrderSent(address buyer, uint text_length);

    /// Event triggerd when newsfeed sends the required ammount
    event PriceSent(address buyer, uint order_nr, uint price);

    /// Event trigger when the buyer sends the ammount
    event PaymentSent(address buyer, uint order_nr, uint value);

    /// Event triggered when the newspaper publishes the article
    event ArticlePublished(address buyer, uint article_nr, uint order_nr, address redactor);


    constructor() payable {
      // the instantiator is the sender
      newsletter =  payable(msg.sender);
    }

    // function for registering the incoming orders
    function SendOrder(bytes32 name, uint text_length) public {

        authors[msg.sender] = Author(msg.sender, name);
        orders[order_seqence] = Order(msg.sender, text_length, 0);
        
        emit OrderSent(msg.sender, text_length);
        SendPrice(order_seqence);
        order_seqence++;

    }

    // function for generating the price for the order and sending it back
    function SendPrice(uint order_nr) private {
        Order memory order = orders[order_nr];

        uint price = order.text_length * 2;
        orders[order_nr].price = price;
        emit PriceSent(order.author_address, order_nr, price);
    }

    // function for receiving the payment together with the text
    function SendPayment(uint order_nr, string memory text) payable public {
        require(
            orders[order_nr].author_address == msg.sender,
            "The sender and the order author addresses are not the same");

        require(
            msg.value >= orders[order_nr].price,
            "The payable ammount is not big enough"
        );

        emit PaymentSent(msg.sender, order_nr, msg.value);
        PublishArticle(order_nr, text);
        article_sequence++;
    }

    // function for publishing the text and paying out the redactor
    function PublishArticle(uint order_nr, string memory text) public {
        articles[article_sequence] = Article(orders[order_nr].author_address, text, order_nr);

        emit ArticlePublished(orders[order_nr].author_address, article_sequence, order_nr, redactor);
        redactor.transfer(orders[order_nr].price);
    }

    function QueryArticle(uint article_nr) view public returns(address, string memory, uint) {

        Article memory _article = articles[article_nr];
        return (_article.article_author_address, _article.article_text, _article.order_number);
    }

    function QueryAuthor(address author_address) view public returns(address, bytes32) {

        Author memory _author = authors[author_address];
        return (_author.author_address, _author.author_name);
    }



}