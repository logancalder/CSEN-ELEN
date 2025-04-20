import React, { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import "./style-help.css";
import logo from "./recycle.png";
import demo from "./demo.png"

const Help = () => {
  const [isScrolled, setIsScrolled] = useState(false);

  useEffect(() => {
    const handleScroll = () => {
      setIsScrolled(window.scrollY > 0);
    };
    window.addEventListener("scroll", handleScroll);
    return () => window.removeEventListener("scroll", handleScroll);
  }, []);

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
            <li className="nav-button">
              <Link to="/faq">FAQ</Link>
            </li>
            <li className="nav-button" id="selected">AI Help</li>
          </ul>
        </nav>
      </div>

      <div className="header">
        <div className="header-text">
          <div className="intro">
            How to use our <br />
            <span id="name">AI Scanner...</span>.
          </div>
          <div className="bio">
            The scanner is easy to use and user-friendly, allowing for quick
            and easy analysis of waste. To get started with the scanner, open
            it using the button below.
          </div>
          <div className="buttons">
            <button id="colored-button">AI Scanner</button>
          </div>
        </div>
        <img src={demo} id="img" alt="demo" />
      </div>

      <div className="content">
        <h1>Tutorial</h1>
        <p>
          To figure out what to do with your waste, upload a picture of it to
          the scanner. The AI will then look it over and provide you
          suggestions!
          <br />
          <br />
          The scanner will initially provide two options: one reuse, and one
          dispose. If you do not like the reuse option (generally how to reuse
          the food item), you may regenerate the answer. This way, you can
          discover multiple new and exciting recipes for your food scraps!
          <br />
          <br />
          Some items are not compostable, and others are better for your soil
          than others. The scanner will provide a compost rating which informs
          you how strong it will be for compost, and how to properly do so!
        </p>
      </div>
    </div>
  );
};

export default Help;
