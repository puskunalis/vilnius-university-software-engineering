import random
import string
import time
import unittest

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import Select, WebDriverWait


def generate_random_string(length):
    letters = string.ascii_lowercase

    return ''.join(random.choice(letters) for _ in range(length))


def generate_random_email():
    return f"{generate_random_string(20)}@{generate_random_string(10)}.com"


def generate_random_password():
    return generate_random_string(20) + "123@"


def get_strings_from_file(filename):
    file = open(filename, 'r')
    strings = file.readlines()
    file.close()

    strings = [i.strip() for i in strings]

    return strings


class DemoWebShopTest(unittest.TestCase):

    email = ""
    password = ""

    def setUp(self):
        self.driver = webdriver.Firefox()
        self.driver.implicitly_wait(10)

    def run_test_with_item_list(self, item_list):
        driver = self.driver

        driver.get("https://demowebshop.tricentis.com/")

        driver.find_element(By.CLASS_NAME, "ico-login").click()

        driver.find_element(By.ID, "Email").send_keys(self.__class__.email)
        driver.find_element(By.ID, "Password").send_keys(
            self.__class__.password)

        driver.find_element(By.CLASS_NAME, "login-button").click()

        driver.find_element(By.LINK_TEXT, "Digital downloads").click()

        for item in item_list:
            driver.find_element(
                By.XPATH, f"//div[@class='item-box']//a[text()='{item}']/ancestor::div[@class='item-box']//input[@value='Add to cart']").click()

            # Sleep in between adding items to cart
            time.sleep(1)

        driver.find_element(By.LINK_TEXT, "Shopping cart").click()

        driver.find_element(By.ID, "termsofservice").click()

        driver.find_element(By.ID, "checkout").click()

        try:
            Select(driver.find_element(By.ID, "BillingNewAddress_CountryId")
                   ).select_by_visible_text("Vatican City State (Holy See)")

            driver.find_element(
                By.ID, "BillingNewAddress_City").send_keys("Test City")

            driver.find_element(By.ID, "BillingNewAddress_Address1").send_keys(
                "Test st. 123-45")

            driver.find_element(
                By.ID, "BillingNewAddress_ZipPostalCode").send_keys("12345")

            driver.find_element(
                By.ID, "BillingNewAddress_PhoneNumber").send_keys("1234567890")
        except:
            pass

        driver.find_element(
            By.CLASS_NAME, "new-address-next-step-button").click()

        WebDriverWait(driver, 20).until(EC.element_to_be_clickable(
            (By.CLASS_NAME, "payment-method-next-step-button"))).click()

        WebDriverWait(driver, 20).until(EC.element_to_be_clickable(
            (By.CLASS_NAME, "payment-info-next-step-button"))).click()

        WebDriverWait(driver, 20).until(EC.element_to_be_clickable(
            (By.CLASS_NAME, "confirm-order-next-step-button"))).click()

        self.assertIsNotNone(driver.find_element(
            By.XPATH, "//strong[text()='Your order has been successfully processed!']"))

    # This should be run first
    def test_1_register_user(self):
        driver = self.driver

        self.__class__.email = generate_random_email()
        self.__class__.password = generate_random_password()

        driver.get("https://demowebshop.tricentis.com/")

        driver.find_element(By.CLASS_NAME, "ico-login").click()

        driver.find_element(
            By.CLASS_NAME, "register-block").find_element(By.CLASS_NAME, "register-button").click()

        driver.find_element(By.ID, "gender-male").click()
        driver.find_element(By.ID, "FirstName").send_keys("TestFirstName")
        driver.find_element(By.ID, "LastName").send_keys("TestLastName")
        driver.find_element(By.ID, "Email").send_keys(self.__class__.email)
        driver.find_element(By.ID, "Password").send_keys(
            self.__class__.password)
        driver.find_element(By.ID, "ConfirmPassword").send_keys(
            self.__class__.password)
        driver.find_element(By.ID, "register-button").click()
        driver.find_element(By.CLASS_NAME, "register-continue-button").click()

    def test_data1(self):
        item_list = get_strings_from_file("data1.txt")
        self.run_test_with_item_list(item_list)

    def test_data2(self):
        item_list = get_strings_from_file("data2.txt")
        self.run_test_with_item_list(item_list)

    def tearDown(self):
        self.driver.quit()


if __name__ == "__main__":
    unittest.main()
