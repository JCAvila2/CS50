document.addEventListener('DOMContentLoaded', function() {

    let scroll_button = document.getElementById("scroll_button");

    // Show the button when the user scrolls down 100px from the top of the document
    window.onscroll = function() {
        if (document.body.scrollTop > 100 || document.documentElement.scrollTop > 100) 
        {
            scroll_button.style.display = "block";
        } 
        else 
        {
            scroll_button.style.display = "none";
        }
    };

    // Scroll to the top of the document when the user clicks on the button
    scroll_button.addEventListener("click", function() {
        document.documentElement.scrollTop = 0;
    });

});