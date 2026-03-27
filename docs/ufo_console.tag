<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.8">
  <compound kind="file">
    <name>u_cns_blank.h</name>
    <path>impl/</path>
    <filename>u__cns__blank_8h.html</filename>
    <class kind="class">__u_console::blank_t</class>
  </compound>
  <compound kind="file">
    <name>u_cns_console.h</name>
    <path>impl/</path>
    <filename>u__cns__console_8h.html</filename>
    <includes id="u__cns__blank_8h" name="u_cns_blank.h" local="yes" import="no" module="no" objc="no">u_cns_blank.h</includes>
    <class kind="class">__u_console::console_t</class>
  </compound>
  <compound kind="file">
    <name>u_cns_io_base.h</name>
    <path>impl/</path>
    <filename>u__cns__io__base_8h.html</filename>
    <class kind="class">__u_console::io_base_t</class>
  </compound>
  <compound kind="file">
    <name>u_cns_streambuf.h</name>
    <path>impl/</path>
    <filename>u__cns__streambuf_8h.html</filename>
    <class kind="class">__u_console::u_cns_streambuf_t</class>
  </compound>
  <compound kind="file">
    <name>u_cns_uart_stream.h</name>
    <path>impl/</path>
    <filename>u__cns__uart__stream_8h.html</filename>
  </compound>
  <compound kind="file">
    <name>u_cns.h</name>
    <path></path>
    <filename>u__cns_8h.html</filename>
    <includes id="u__cns__console_8h" name="u_cns_console.h" local="yes" import="no" module="no" objc="no">impl/u_cns_console.h</includes>
    <includes id="u__cns__uart__stream_8h" name="u_cns_uart_stream.h" local="yes" import="no" module="no" objc="no">impl/u_cns_uart_stream.h</includes>
  </compound>
  <compound kind="class">
    <name>__u_console::blank_t</name>
    <filename>class____u__console_1_1blank__t.html</filename>
  </compound>
  <compound kind="class">
    <name>__u_console::console_t</name>
    <filename>class____u__console_1_1console__t.html</filename>
    <member kind="typedef">
      <type>void(*)()</type>
      <name>post_run_callback_t</name>
      <anchorfile>class____u__console_1_1console__t.html</anchorfile>
      <anchor>af500125beea0b6acfa8c88bc7c9cf970</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>console_t</name>
      <anchorfile>class____u__console_1_1console__t.html</anchorfile>
      <anchor>a71f1d5a8349216a556eb82e7bfb39329</anchor>
      <arglist>(io_base_t *port, size_t buf_sz, pre_run_callback_t pre_clb=nullptr, post_run_callback_t post_clb=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>console_t</name>
      <anchorfile>class____u__console_1_1console__t.html</anchorfile>
      <anchor>afec808f4a3b8c28abb58afc899fa7263</anchor>
      <arglist>(console_t &amp;&amp;oth)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mk_blank</name>
      <anchorfile>class____u__console_1_1console__t.html</anchorfile>
      <anchor>a3346790df8bfcd44926cab02569e08d2</anchor>
      <arglist>(const char *cl_name, const char *desc, blank_t::callback_t foo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rm_blank</name>
      <anchorfile>class____u__console_1_1console__t.html</anchorfile>
      <anchor>a9475fc905c6f94e5894552a692a68ab5</anchor>
      <arglist>(const char *cl_name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ctask</name>
      <anchorfile>class____u__console_1_1console__t.html</anchorfile>
      <anchor>ac5723b14133f5609be57a66ea3345919</anchor>
      <arglist>(ufo::token_t token)</arglist>
    </member>
    <docanchor file="class____u__console_1_1console__t.html" title="Registration commands">registration</docanchor>
    <docanchor file="class____u__console_1_1console__t.html" title="Internal Commands">internal_commands</docanchor>
    <docanchor file="class____u__console_1_1console__t.html" title="Thread safety">threading</docanchor>
    <docanchor file="class____u__console_1_1console__t.html" title="Move-only semantics">move_only</docanchor>
  </compound>
  <compound kind="struct">
    <name>Console_parser::parser::ind_t</name>
    <filename>struct_console__parser_1_1parser_1_1ind__t.html</filename>
  </compound>
  <compound kind="class">
    <name>__u_console::io_base_t</name>
    <filename>class____u__console_1_1io__base__t.html</filename>
  </compound>
  <compound kind="class">
    <name>__u_console::msg_block_t</name>
    <filename>class____u__console_1_1msg__block__t.html</filename>
    <docanchor file="class____u__console_1_1msg__block__t.html" title="Information output">output</docanchor>
    <docanchor file="class____u__console_1_1msg__block__t.html" title="Parsing arguments">parsing</docanchor>
    <docanchor file="class____u__console_1_1msg__block__t.html" title="Reading additional input">reading</docanchor>
  </compound>
  <compound kind="struct">
    <name>Console_parser::parser::opt_ind_t</name>
    <filename>struct_console__parser_1_1parser_1_1opt__ind__t.html</filename>
  </compound>
  <compound kind="class">
    <name>Console_parser::parser</name>
    <filename>class_console__parser_1_1parser.html</filename>
    <class kind="struct">Console_parser::parser::ind_t</class>
    <class kind="struct">Console_parser::parser::opt_ind_t</class>
    <member kind="function">
      <type></type>
      <name>parser</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>a1d2199528156bb5dd4e61e57618deb29</anchor>
      <arglist>(const std::string &amp;s, bool parse_prog_name=false, bool strict=false, const char *separators=default_line_separators)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>parser</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>aaec293bca2e780564f18ffe97eceae7c</anchor>
      <arglist>(std::string &amp;&amp;s, bool parse_prog_name=false, bool strict=false, const char *separators=default_line_separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parse</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>a892ff48af061b1bf2eb58be960062ce5</anchor>
      <arglist>(const std::string &amp;s, bool parse_prog_name=false, const char *separators=default_line_separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parse</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>a3027cb7745181e6143bdd4a39a562799</anchor>
      <arglist>(std::string &amp;&amp;s, bool parse_prog_name=false, const char *separators=default_line_separators)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>a8b69e2896cb7326efa366b783ed21027</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>good</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>ad0e3276c201b88626b989b47b422ff42</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>log</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>aa1bce278bb748cda574f08f9068c8833</anchor>
      <arglist>(std::ostream &amp;os) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bind</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>a396a60eea75fe92c1c22f7304ff9e7ee</anchor>
      <arglist>(Ty *var, const std::string &amp;token) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>find</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>aa05a9538d18492a537ae7df7cb292729</anchor>
      <arglist>(const std::string &amp;token) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>bind</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>a9a4fdeedfc4d5d6673c174e543260f0a</anchor>
      <arglist>(std::vector&lt; Ty &gt; *arr, const std::string &amp;token) const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_prog_name</name>
      <anchorfile>class_console__parser_1_1parser.html</anchorfile>
      <anchor>aab28fda65a22ebe7e49397dc977d7ac2</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>__u_console::u_cns_streambuf_t</name>
    <filename>class____u__console_1_1u__cns__streambuf__t.html</filename>
  </compound>
  <compound kind="group">
    <name>public_api</name>
    <title>Public API</title>
    <filename>group__public__api.html</filename>
    <file>u_cns_console.h</file>
    <file>u_cns.h</file>
    <class kind="class">__u_console::console_t</class>
    <class kind="class">__u_console::msg_block_t</class>
    <member kind="typedef">
      <type>__u_console::console_t</type>
      <name>ufo::u_console_t</name>
      <anchorfile>group__public__api.html</anchorfile>
      <anchor>ga0d9c7c2a076331eb26b653e43a54ef07</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>__u_console::msg_block_t</type>
      <name>ufo::u_console_msg_block_t</name>
      <anchorfile>group__public__api.html</anchorfile>
      <anchor>ga4892b789a9986075eeff2c0c5a6a4e0d</anchor>
      <arglist></arglist>
    </member>
    <page>group__public__api</page>
  </compound>
  <compound kind="group">
    <name>impl_details</name>
    <title>Implementation details</title>
    <filename>group__impl__details.html</filename>
    <file>u_cns_blank.h</file>
    <file>u_cns_io_base.h</file>
    <file>u_cns_streambuf.h</file>
    <file>u_cns_uart_stream.h</file>
  </compound>
  <compound kind="page">
    <name>external_parser</name>
    <title>Console-parser</title>
    <filename>group__public__api.html</filename>
    <docanchor file="group__public__api.html" title="Введение">intro_parser</docanchor>
    <docanchor file="group__public__api.html" title="Сapability">features_parser</docanchor>
    <docanchor file="group__public__api.html" title="Usage in UFO Console">usage_parser</docanchor>
    <docanchor file="group__public__api.html" title="Parsing examples">examples_parser</docanchor>
    <docanchor file="group__public__api.html" title="Arguments">example_simple</docanchor>
    <docanchor file="group__public__api.html" title="Arrays">example_array</docanchor>
    <docanchor file="group__public__api.html" title="Double quotes">example_quoted</docanchor>
    <docanchor file="group__public__api.html" title="Aliases">example_aliases</docanchor>
    <docanchor file="group__public__api.html" title="Basic methods">methods_parser</docanchor>
    <docanchor file="group__public__api.html" title="Strict mode">strict_mode</docanchor>
    <docanchor file="group__public__api.html" title="Full documentation">full_docs</docanchor>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>UFO Console Module</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="Introduction">intro</docanchor>
    <docanchor file="index.html" title="Сapabilities">features</docanchor>
    <docanchor file="index.html" title="Архитектура">architecture</docanchor>
    <docanchor file="index.html" title="Quick start">quick_start</docanchor>
    <docanchor file="index.html" title="Dependencies">dependencies</docanchor>
  </compound>
</tagfile>
