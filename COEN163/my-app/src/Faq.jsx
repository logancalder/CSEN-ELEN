import React, { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import "./style.css";
import logo from "./recycle.png";

const Faq = () => {
  const [isScrolled, setIsScrolled] = useState(false);
  const [isMobileNavOpen, setIsMobileNavOpen] = useState(false);

  useEffect(() => {
    const handleScroll = () => {
      setIsScrolled(window.scrollY > 0);
    };
    window.addEventListener("scroll", handleScroll);
    return () => window.removeEventListener("scroll", handleScroll);
  }, []);

  const toggleNavBar = () => {
    setIsMobileNavOpen(!isMobileNavOpen);
  };

  return (
    <div>
      <div className={`nav-bar ${isScrolled ? "scrolled" : ""}`}>
        <Link to="/home">
          <img className="logo" src={logo} alt="logo" />
        </Link>
        <nav className="nav">
          <ul>
            <li className="nav-button">
              <Link to="/info">Information</Link>
            </li>
            <li className="nav-button">
              <Link to="/ideas">Ideas</Link>
            </li>
            <li className="nav-button" id="selected">
              FAQ
            </li>
            <li className="nav-button">
              <Link to="/help">AI Help</Link>
            </li>
          </ul>
        </nav>
        <div onClick={toggleNavBar} className="nav-menu-container">
          <i className="fa-solid fa-bars" id="nav-menu-button"></i>
        </div>
      </div>

      <div id="mobile-nav-bar" className={isMobileNavOpen ? "fade" : ""}>
        <ul>
          <li className="nav-button">
            <Link to="/info">Information</Link>
          </li>
          <li className="nav-button">
            <Link to="/ideas">Ideas</Link>
          </li>
          <li className="nav-button">
            <Link to="/help">AI Help</Link>
          </li>
        </ul>
      </div>

      <div className="content">
        <div>
          <h1 className="title">
            Frequently Asked<span id="gradient"> Questions</span>
          </h1>
          <img src="compost.jpg" id="about-mobile" alt="compost" />
          <div id="bio">
            <h2>How do I use the AI Scanner?</h2>
            <p>
              Our AI Scanner is extremely easy to use! You may utilize it by clicking on the home screen{" "}
              <span id="highlight">AI Scanner button</span>. If you would like to learn more, visit the{" "}
              <Link to="/help" id="highlight">
                AI Help page.
              </Link>
            </p>

            <h2>How do I compost?</h2>
            <p>Composting is a simple process that can be done at home. Here are the key steps:</p>
            <ol>
              <li>
                <span id="highlight">Choose a compost bin</span>: Select a bin that suits your needs and space.
              </li>
              <li>
                <span id="highlight">Add compostable materials</span>: Include a mix of green (e.g., fruit and vegetable scraps) and brown (e.g., leaves, cardboard) materials.
              </li>
              <li>
                <span id="highlight">Maintain the compost</span>: Turn the compost regularly to aerate it and keep it moist.
              </li>
              <li>
                <span id="highlight">Harvest the compost</span>: Once the compost is dark and crumbly, it is ready to use in your garden.
              </li>
            </ol>

            <h2>What are some ways to reduce food waste?</h2>
            <p>There are many ways to reduce food waste, including:</p>
            <ul>
              <li>
                <span id="highlight">Plan meals</span>: Create a meal plan to avoid buying excess food.
              </li>
              <li>
                <span id="highlight">Store food properly</span>: Keep food fresh by storing it in airtight containers.
              </li>
              <li>
                <span id="highlight">Use leftovers</span>: Repurpose leftovers into new meals to avoid waste.
              </li>
            </ul>

            <h2>How can I reuse food scraps?</h2>
            <p>Food scraps can be reused in various ways, such as:</p>
            <ul>
              <li>
                <span id="highlight">Composting</span>: Turn food scraps into nutrient-rich compost for your garden.
              </li>
              <li>
                <span id="highlight">Broths and stocks</span>: Use vegetable scraps to make flavorful broths and stocks.
              </li>
              <li>
                <span id="highlight">Smoothies</span>: Blend fruit and vegetable scraps into delicious smoothies.
              </li>
            </ul>

            <h2>What is this website?</h2>
            <p>
              This website is designed to educate users on sustainable practices, such as composting, reducing food waste, and reusing food scraps. Our goal is to promote environmental awareness and provide practical tips for living a more eco-friendly lifestyle.
            </p>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Faq;
