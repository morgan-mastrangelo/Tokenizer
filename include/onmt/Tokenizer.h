#pragma once

#include <unordered_map>

#include "onmt/ITokenizer.h"
#include "onmt/BPE.h"

namespace onmt
{

  // This Tokenizer implements the behaviour of OpenNMT's tools/tokenize.lua.
  class Tokenizer: public ITokenizer
  {
  public:
    enum class Mode
    {
      Conservative,
      Aggressive,
      Space
    };

    static const std::string joiner_marker;
    static const std::string ph_marker_open;
    static const std::string ph_marker_close;

    static const std::unordered_map<std::string, onmt::Tokenizer::Mode> mapMode;

    Tokenizer(Mode mode = Mode::Conservative,
              const std::string& bpe_model_path = "",
              bool case_feature = false,
              bool joiner_annotate = false,
              bool joiner_new = false,
              const std::string& joiner = joiner_marker,
              bool with_separators = false,
              bool segment_case = false,
              bool segment_numbers = false,
              bool cache_bpe_model = false);
    Tokenizer(bool case_feature = false,
              const std::string& joiner = joiner_marker);
    ~Tokenizer();

    void tokenize(const std::string& text,
                  std::vector<std::string>& words,
                  std::vector<std::vector<std::string> >& features) override;

    std::string detokenize(const std::vector<std::string>& words,
                           const std::vector<std::vector<std::string> >& features) override;

  private:
    Mode _mode;
    BPE* _bpe;
    bool _case_feature;
    bool _joiner_annotate;
    bool _joiner_new;
    std::string _joiner;
    bool _with_separators;
    bool _segment_case;
    bool _segment_numbers;
    bool _cache_bpe_model;

    std::vector<std::string> bpe_segment(const std::vector<std::string>& tokens);

    bool has_left_join(const std::string& word);
    bool has_right_join(const std::string& word);
  };

}
