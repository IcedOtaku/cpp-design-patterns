#include <cdps/cdps.h>

#include <iostream>

#pragma mark - init

void init_cdps() {
  std::string version = cdps::version::get_version_in_cpp();
  std::cout << "cdps " << version << " initialized" << std::endl;
}

#pragma mark - singleton

void test_singleton() {
  cdps::singleton* p = cdps::singleton::get();
  std::cout << p->desc << std::endl;
}

#pragma mark - chain_of_responsibility

cdps::logger* get_logger() {
  cdps::logger* error_logger = new cdps::error_logger(cdps::log_level::log_level_error);
  cdps::logger* info_logger = new cdps::info_logger(cdps::log_level::log_level_info);
  cdps::logger* debug_logger = new cdps::debug_logger(cdps::log_level::log_level_debug);
  error_logger->set_next(info_logger);
  info_logger->set_next(debug_logger);

  return error_logger;
}

void test_chain_of_responsibility() {
  cdps::logger* logger = get_logger();
  logger->log_message(cdps::log_level::log_level_debug, "this is debug");
  logger->log_message(cdps::log_level::log_level_info, "this is info");
  logger->log_message(cdps::log_level::log_level_error, "this is error");
}

#pragma mark - observer

void test_observer() {
  cdps::subject* sub = new cdps::subject();
  new cdps::bin_observer(sub);
  new cdps::oct_observer(sub);
  new cdps::hex_observer(sub);

  sub->set_state(10);
  sub->set_state(15);
}

#pragma mark - decorator

void test_decorator() {
  cdps::circle_shape* circle = new cdps::circle_shape();
  circle->draw();

  cdps::red_shape_decorator* circle_decorator = new cdps::red_shape_decorator(circle);
  circle_decorator->draw();

  cdps::rectangle_shape* rectangle = new cdps::rectangle_shape();
  rectangle->draw();

  cdps::red_shape_decorator* rectangle_decorator = new cdps::red_shape_decorator(rectangle);
  rectangle_decorator->draw();
}

#pragma mark - main

int main(int argc, char* argv[]) {
  init_cdps();
  test_decorator();
  return 0;
}
