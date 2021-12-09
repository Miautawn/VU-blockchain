// SPDX-License-Identifier: MIT
pragma solidity >=0.4.22 <0.9.0;

import "truffle/Assert.sol";
import "truffle/DeployedAddresses.sol";
import "../contracts/Newspaper.sol";

contract TestNewspaper{
  // The address of the adoption contract to be tested
  Newspaper newspaper = Newspaper(DeployedAddresses.Newspaper());

  // The address of the order sender which is me
  bytes32 expectedOrderAutorName = "Hello";

  // Testing the adopt() function
  function testOrderSending() public {
    
    newspaper.SendOrder("Hello", 32);
    (, bytes32 author_name) = newspaper.QueryAuthor(address(this));

    Assert.equal(author_name, expectedOrderAutorName, "sent author name and the current should match.");
  }
}
