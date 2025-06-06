std::pair<double, double> getAbsSciDepth(double depth, double sci_abs_ratio, double n_layer) {
    double layer_thickness = depth / n_layer;
    double sci_depth = layer_thickness * sci_abs_ratio;
    double abs_depth = layer_thickness - sci_depth;

    return std::make_pair(sci_depth, abs_depth);
}

void makeConfigs() {
    double hcal_depth = 70 //cm
    std::vector<double> sci_abs_ratios = {0.2, 0.4, 0.6, 0.8};
    std::vector<double> n_layers = {10, 15, 20, 25};

    std::cout << getAbsSciDepth(44, 0.1, 10).first << std::endl; // Example usage of getAbsSciDepth

    // for (double sci_abs_ratio : sci_abs_ratios) {
    //     for (double n_layer : n_layers) {
    //         std::string config_name = "config_sci_" + std::to_string(sci_abs_ratio) + "_layers_" + std::to_string(n_layer);
    //         std::cout << "Creating configuration: " << config_name << std::endl;
    //         // Here you would typically call a function to create the configuration
    //         // createConfiguration(config_name, hcal_depth, sci_abs_ratio, n_layer);
    //     }
    // }
}
