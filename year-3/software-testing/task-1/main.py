import random
import string
import unittest

from selenium import webdriver
from selenium.webdriver.common.by import By

def generate_random_email():
    letters = string.ascii_lowercase

    email_username = ''.join(random.choice(letters) for _ in range(20))
    email_domain = ''.join(random.choice(letters) for _ in range(20))

    email = f"{email_username}@{email_domain}.com"

    return email

class DemoWebShopTest(unittest.TestCase):

    def setUp(self):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(10)

    def test_demo_web_shop(self):
        driver = self.driver

        email = generate_random_email()

        driver.get("https://demowebshop.tricentis.com/")

        driver.find_element(By.CLASS_NAME, "ico-login").click()

        driver.find_element(By.CLASS_NAME, "register-block").find_element(By.CLASS_NAME, "register-button").click()

        driver.find_element(By.ID, "gender-male").click()
        driver.find_element(By.ID, "FirstName").send_keys("TestFirstName")
        driver.find_element(By.ID, "LastName").send_keys("TestLastName")
        driver.find_element(By.ID, "Email").send_keys(email)
        driver.find_element(By.ID, "Password").send_keys("TestPassword123")
        driver.find_element(By.ID, "ConfirmPassword").send_keys("TestPassword123")
        driver.find_element(By.ID, "register-button").click()
        driver.find_element(By.CLASS_NAME, "register-continue-button").click()

        driver.find_element(By.CLASS_NAME, "block-category-navigation").find_element(By.LINK_TEXT, "Computers").click()
        driver.find_element(By.CLASS_NAME, "block-category-navigation").find_element(By.LINK_TEXT, "Desktops").click()

        driver.find_element(By.XPATH, "//span[contains(@class,'price') and text()>1500]/parent::div/following-sibling::div[@class='buttons']/input[@value='Add to cart']").click()

        driver.find_element(By.CLASS_NAME, "add-to-cart-button").click()

        driver.find_element(By.LINK_TEXT, "Shopping cart").click()

        driver.find_element(By.XPATH, "//input[@type='checkbox' and @name='removefromcart']").click()

        driver.find_element(By.CLASS_NAME, "update-cart-button").click()

        self.assertIn("Your Shopping Cart is empty!", driver.page_source)

    def tearDown(self):
        self.driver.quit()

if __name__ == "__main__":
    unittest.main()
