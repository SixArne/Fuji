add_custom_command(TARGET VulkanEngine POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/Shaders" "$<TARGET_FILE_DIR:VulkanEngine>/Shaders"
)