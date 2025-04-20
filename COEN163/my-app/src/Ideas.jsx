import React, { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import "./style-ideas.css";
import logo from "./recycle.png";
import recycle from "./recycle.png";

const Ideas = () => {
  const [isScrolled, setIsScrolled] = useState(false);
  const [selectedCategory, setSelectedCategory] = useState("Skills");
  const [skillsContent, setSkillsContent] = useState("");
  const [mobileNavVisible, setMobileNavVisible] = useState(false);

  useEffect(() => {
    const handleScroll = () => {
      setIsScrolled(window.scrollY > 0);
    };
    window.addEventListener("scroll", handleScroll);
    return () => window.removeEventListener("scroll", handleScroll);
  }, []);

  const handleSelection = (category) => {
    setSelectedCategory(category);
    switch (category) {
      case "Skills":
        setSkillsContent(
          "Python, C, C++, C#, Golang, Java, JavaScript, HTML & CSS, K8, Docker"
        );
        break;
      case "Experience":
        setSkillsContent(
          "Software Engineering Intern @ HPE Stanford Treehacks 2023 Nominee \nResearch Assistant @ SCU"
        );
        break;
      default:
        setSkillsContent(
          "Santa Clara University, B.S. 2025\nComputer Science & Engineering"
        );
    }
  };

  const scrollToDiv = () => {
    document.getElementById("connect").scrollIntoView({
      behavior: "smooth",
      block: "center",
    });
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
            <li className="nav-button" id="selected">
              Ideas
            </li>
            <li className="nav-button">
              <Link to="/faq">FAQ</Link>
            </li>
            <li className="nav-button">
              <Link to="/help">AI Help</Link>
            </li>
          </ul>
        </nav>
        <div onClick={() => setMobileNavVisible(!mobileNavVisible)} className="nav-menu-container">
          <i className="fa-solid fa-bars" id="nav-menu-button"></i>
        </div>
      </div>

      {mobileNavVisible && (
        <div id="mobile-nav-bar">
          <ul>
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
        </div>
      )}

      <div className="header">
        <div className="header-text">
          <div className="intro">
            Hi there, let's talk<br />
            <span id="name">recycling</span>.
          </div>
          <div className="bio">
            We have some ideas on how you can conserve, reuse, and compost foods!
          </div>
          <div className="buttons">
            <button id="colored-button">AI Scanner</button>
            <button id="transparent-button">Our Mission</button>
          </div>
        </div>
        <img src={recycle} id="img" alt="Recycle" />
      </div>

      <img src={recycle} id="img_mobile" alt="Recycle Mobile" />

      <div className="content">
        <h1>My Ideas...</h1>
        <p>
          This app will feature a smart AI scanner, capable of analyzing pictures that you take of leftover food! From here, it will suggest recipes that can be composed from the food shown, or how to properly dispose of it. If compostable, which most are, it will state that as well. Various foods have a higher "compost rating," and so the AI will display out of five stars how great it is for your crops!
          <br />
          <br />
          I also would like to have some hand-picked videos that showcase the best composting practices, and how easy it is to do at home. Further, I want to also showcase what organic matter may be disposed of in the green bins. Since the user uses AI, a user login page will be made.
          <br />
          <br />
          Users may find this site by Googling for it, and may click on login with Google to use it. To ask AI, one may click on the AI Scanner button on this page.
        </p>
      </div>
    </div>
  );
};

export default Ideas;
