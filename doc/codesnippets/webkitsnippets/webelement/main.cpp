
def traverse():
//! [Traversing with QWebElement]
    frame.setHtml("<html><body><p>First Paragraph</p><p>Second Paragraph</p></body></html>")
    doc = frame.documentElement()
    body = doc.firstChild()
    firstParagraph = body.firstChild()
    secondParagraph = firstParagraph.nextSibling()
//! [Traversing with QWebElement]

def findButtonAndClick():
    frame.setHtml("<form name=\"myform\" action=\"submit_form.asp\" method=\"get\">" \
                   "<input type=\"text\" name=\"myfield\">" \
                   "<input type=\"submit\" value=\"Submit\">" \
                   "</form>")

//! [Calling a DOM element method]

    document = frame.documentElement()
    # Assume that the document has the following structure:
    #
    #    <form name="myform" action="submit_form.asp" method="get">
    #        <input type="text" name="myfield">
    #        <input type="submit" value="Submit">
    #    </form>

    button = document.findFirst("input[type=submit]")
    button.evaluateJavaScript("click()")

//! [Calling a DOM element method]

def autocomplete1():
    document = frame.documentElement()
//! [autocomplete1]
    firstTextInput = document.findFirst("input[type=text]")
    storedText = firstTextInput.attribute("value")
//! [autocomplete1]

def autocomplete2():
    document = frame.documentElement()
    storedText = "text"

//! [autocomplete2]
    firstTextInput = document.findFirst("input[type=text]")
    textInput.setAttribute("value", storedText)
//! [autocomplete2]

def findAll():
//! [FindAll]
    document = frame.documentElement()
    # Assume the document has the following structure:
    #
    #   <p class=intro>
    #     <span>Intro</span>
    #     <span>Snippets</span>
    #   </p>
    #   <p>
    #     <span>Content</span>
    #     <span>Here</span>
    #   </p>

//! [FindAll intro]
    allSpans = document.findAll("span")
    introSpans = document.findAll("p.intro span")
//! [FindAll intro] //! [FindAll]
