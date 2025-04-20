import React, { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import "./style-ideas.css";
import logo from "./recycle.png";
import compost from "./compost.jpg";

const Info = () => {
  const [isScrolled, setIsScrolled] = useState(false);
  const [isPopupVisible, setIsPopupVisible] = useState(true);
  const [email, setEmail] = useState("");

  useEffect(() => {
    const handleScroll = () => {
      setIsScrolled(window.scrollY > 0);
    };
    window.addEventListener("scroll", handleScroll);
    return () => window.removeEventListener("scroll", handleScroll);
  }, []);

  const closePopup = () => {
    setIsPopupVisible(false);
  };

  return (
    <div>
      <div className={`nav-bar ${isScrolled ? "scrolled" : ""}`}>
        <Link to="/home">
          <img className="logo" src={logo} alt="logo" />
        </Link>
        <nav className="nav">
          <ul>
            <li className="nav-button" id="selected">
              <Link to="#">Information</Link>
            </li>
            <li className="nav-button">
              <Link to="/ideas">Ideas</Link>
            </li>
            <li className="nav-button">
              <Link to="/faq">FAQ</Link>
            </li>
            <li className="nav-button">
              <Link to="/help">AI Help</Link>
            </li>
          </ul>
        </nav>
      </div>

      {isPopupVisible && (
        <div id="welcomePopup" className="popup">
          <h2>Welcome!</h2>
          <p>Enter your email to stay updated:</p>
          <input
            type="email"
            placeholder="Your email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
          />
          <button onClick={closePopup}>Submit</button>
        </div>
      )}

      <div className="content">
        <img src={compost} id="about" alt="compost" />
        <div>
          <h1 className="title">
            General <span id="gradient">information</span>...
          </h1>
          <img src="compost.jpg" id="about-mobile" alt="compost" />
          <div id="bio">
            <h2>
              We are focused on educating others on how to reuse and compost
              food.
            </h2>
            <p>
              Learning to properly dispose of food is <span id="highlight">extremely important</span>, with many people still throwing out excess food waste or scraps daily.
            </p>
            <p>
              Our focus is to train users to learn the proper food management techniques, including not overconsuming, <span id="highlight">composting</span>, and reusing excess food to be combined into new, exciting dishes.
            </p>
            <p>
              Since food is used by everyone, with people of all various ages cooking and handling meals, this site is for everyone! Using <span id="highlight">generative AI</span>, we offer a unique learning opportunity to not only learn what foods make great fertilizer once broken down, but also sharing unique and exciting <span id="highlight">recipes</span> that you would otherwise have no idea how to compose!
            </p>
          </div>
        </div>
      </div>

      <div className="list-container">
        <h1 className="resources">
          <div>
            <span id="gradient">Resources</span>
          </div>
        </h1>
        <ul className="list">
          <li>
            <a href="https://www.nrdc.org/stories/composting-101" target="_blank" rel="noopener noreferrer">Composting 101</a>
          </li>
          <li>
            <a href="https://www.stopwaste.org/at-home/reduce-and-reuse/reducing-wasted-food/food-scrap-composting" target="_blank" rel="noopener noreferrer">Food Scrap Composting</a>
          </li>
          <li>
            <a href="https://www.bbcgoodfood.com/recipes/collection/leftovers-recipes" target="_blank" rel="noopener noreferrer">Leftovers Recipes</a>
          </li>
        </ul>
      </div>
    </div>
  );
};

export default Info;
