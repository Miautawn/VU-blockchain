const Newspaper = artifacts.require("Newspaper");

module.exports = function (deployer) {
  deployer.deploy(Newspaper);
};
